/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 20:45:50 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_finished_ate_last_person(t_philo_node *node_philo)
{
	long	time_current;
	long	time_ate;
	long	timeval;
	long	time_to_eat;

	timeval = get_time_milli_sec();
	if (timeval < 0)
		get_err_num_ph(node_philo->ph, ERR_GETTEIME_MS);
	time_to_eat = node_philo->ph->argv[3];
	time_current = timeval - node_philo->start_time;
	time_ate = node_philo->time[EATING] + time_to_eat;
	if (time_current > time_ate)
		return (true);
	return (false);
}

bool	judge_ate_all(t_philo_main *ph, size_t num_people, t_philo_node *node_philo)
{
	bool wait_ate;

	wait_ate = false;
	x_lock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt == num_people)
	{
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
		
		while (wait_ate == false)
		{
			x_lock_mutex_philo(node_philo);
			if (is_finished_ate_last_person(node_philo) == true)
			{
				x_unlock_mutex_philo(node_philo);
				wait_ate = true;
			}
			x_unlock_mutex_philo(node_philo);
		}
		
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		ph->end_struct.flag_end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		// printf("===============end flag\n");
		
		return (true);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	return (false);
}

static void	set_flag_died(t_philo_main *ph, size_t id)
{
	t_mutex			*mutex_struct;

	mutex_struct = &ph->mutex_struct;

	x_lock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
	ph->died_struct.died_flag = true;
	ph->died_struct.died_id = id;
	x_unlock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);

	x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	ph->end_struct.flag_end = true;
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
}

bool	check_time_to_die(t_philo_node *node_philo, long time_current)
{
	const long	start = node_philo->start_time;
	const long	eating = node_philo->time[EATING];
	const long	time_to_eat = (long)node_philo->ph->argv[2];
	
	if (time_current - (start + eating) >= time_to_eat)
	{
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	return (false);
}

//TODO argv[1]をinitでnum_peopleに
void	*run_rutine_monitor_in_thread(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	size_t	num_people;
	long	time_current;
	bool	end;

	end = false;
	node_monitor = (t_monitor_node *)ptr;
	ph = node_monitor->ph;
	num_people = ph->argv[1];
	while (end == false)
	{
		// die time to eat
		time_current = get_time_milli_sec();
		if (time_current < 0)
			get_err_num_ph(node_monitor->ph, ERR_GETTEIMEOFDAY);
		x_lock_mutex_philo(node_monitor->node_philo);
		check_time_to_die(node_monitor->node_philo, time_current);
		x_unlock_mutex_philo(node_monitor->node_philo);
		// printf("========moni th\n");
		// ate_all
		if (ph->flag_must_eat == true)
			judge_ate_all(ph, num_people, node_monitor->node_philo);
		
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		if (ph->end_struct.flag_end == true)
			end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	}
	return (ptr);
}
