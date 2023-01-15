/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 11:06:45 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_flag_died(t_philo_main *ph, size_t id)
{
	t_mutex			*mutex_struct;

	mutex_struct = &ph->mutex_struct;

	x_lock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
	if (ph->died_struct.died_flag == false)
	{
		// printf("-----die id%ld\n", id);
		ph->died_struct.died_flag = true;
		ph->died_struct.died_id = id;
	}
	x_unlock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);

	x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	ph->end_struct.flag_end = true;
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
}

bool	check_time_to_die(t_philo_node *node_philo, long time_current)
{
	const long	eating = node_philo->time[EATING];
	const long	time_to_eat = (long)node_philo->ph->argv[2];
	
	if (eating > 0 && time_current - eating >= time_to_eat)
	{
		// printf("--check cur_t %ld,  eat %ld,\n", time_current, eating);
		// printf("--t_to_eat %ld, id%ld\n", time_to_eat, node_philo->id);
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	return (false);
}

bool	judge_ate_all(t_philo_main *ph, size_t num_people)
{
	x_lock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt == num_people)
	{
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
		
		usleep(ph->argv[2] * 1000);
	
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		ph->end_struct.flag_end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		
		return (true);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	return (false);
}

//TODO argv[1]をinitでnum_peopleに
void	*run_rutine_monitor_in_thread(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	size_t			num_people;
	size_t 			i;
	t_philo_node	*node_philo;
	long			time_current;

	node_monitor = (t_monitor_node *)ptr;
	ph = node_monitor->ph;
	num_people = ph->argv[1];
	while (1)
	{
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		if (ph->end_struct.flag_end)
		{
			x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
			break ;
		}
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		if (ph->flag_must_eat == true)
		{
			if (judge_ate_all(ph, num_people))
				break ;
		}
		i = 0;
		while (i < num_people)
		{
			node_philo = get_philo_node(&ph->philo_list, i);
			time_current = get_time_milli_sec();
			if (time_current < 0)
				get_err_num_philo(node_philo, ERR_GETTEIME_MS);
			check_time_to_die(node_philo, time_current);
			i++;
		}
	}
	return (ptr);
}
