/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 15:21:20 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct)
{
	bool ret;

	ret = false;
	x_lock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	if (end_struct->flag_end == true)
		ret = true;
	x_unlock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	return (ret);
}

void	set_flag_died(t_philo_main *ph, size_t id)
{
	t_mutex			*mutex_struct;

	mutex_struct = &ph->mutex_struct;

	x_lock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
	if (ph->died_struct.died_flag == false)
	{
		ph->died_struct.died_flag = true;
		ph->died_struct.died_id = id;
	}
	x_unlock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);

	x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	ph->end_struct.flag_end = true;
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
}

bool	judge_ate_all(t_philo_main *ph, size_t num_people)
{
	x_lock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt == num_people)
	{
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
		usleep(ph->argv[3] * 1000);
		x_lock_mutex_struct(&ph->mutex_struct.mutex_ate_all, &ph->mutex_struct);
		ph->ate_struct.ate_all = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_ate_all, &ph->mutex_struct);
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		ph->end_struct.flag_end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		return (true);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	return (false);
}

// bool	check_ate_time_to_die(t_philo_node *node_philo, long time_current)
// {
// 	const long	eating = node_philo->time[EATING];
// 	const long	time_to_eat = (long)node_philo->ph->argv[2];

// 	if (eating > 0 && time_current - eating >= time_to_eat)
// 	{
// 		set_flag_died(node_philo->ph, node_philo->id);
// 		return (true);
// 	}
// 	return (false);
// }
bool	check_ate_time_to_die(t_philo_node *node_philo)
{
	const long	eating = node_philo->time[EATING];
	const long	time_to_eat = (long)node_philo->ph->argv[2];
	long		time_current;

	time_current = get_time_milli_sec();
	if (time_current < 0)
		get_err_num_philo(node_philo, ERR_GETTEIME_MS);

	if (eating > 0 && time_current - eating >= time_to_eat)
	{
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	return (false);
}

bool	judge_time_to_die(t_philo_main *ph, size_t num_people)
{
	size_t i;
	t_philo_node	*node_philo;
	
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		if (check_ate_time_to_die(node_philo))
		{
			x_unlock_mutex_philo(node_philo);
			return (true) ;
		}
		x_unlock_mutex_philo(node_philo);
		i++;
	}
	return (false);
}

void	*run_rutine_monitor_in_thread(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	size_t			num_people;
	// size_t 			i;
	// t_philo_node	*node_philo;

	node_monitor = (t_monitor_node *)ptr;
	ph = node_monitor->ph;
	num_people = node_monitor->num_people;
	while (1)
	{
		if (is_end(&ph->end_struct, &ph->mutex_struct))
			break ;
		if (ph->flag_must_eat == true)
		{
			if (judge_ate_all(ph, num_people))
				break ;
		}
		if (judge_time_to_die(ph, num_people))
			break ;
		// i = 0;
		// while (i < num_people)
		// {
		// 	node_philo = get_philo_node(&ph->philo_list, i);
		// 	x_lock_mutex_philo(node_philo);
		// 	if (check_ate_time_to_die(node_philo))
		// 	{
		// 		x_unlock_mutex_philo(node_philo);
		// 		return (ptr) ;
		// 	}
		// 	x_unlock_mutex_philo(node_philo);
		// 	i++;
		// }
	}
	return (ptr);
}
