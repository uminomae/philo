/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 01:28:04 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct);
bool	judge_ate_all(t_philo_main *ph, size_t num_people);

// need usleep(1000)? died put 
void	*run_rutine_monitor(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	size_t			num_people;
	long		time;
	
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
	}
	if (ph->died_struct.died_flag == true)
	{
		if (!gettimeofday_millisec(ph, &time))
			return (false);
		put_stamp(time, ph->died_struct.died_id, DIED_STR);
	}
	return (ptr);
}

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
