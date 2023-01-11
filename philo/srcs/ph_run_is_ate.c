/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_is_ate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/12 07:29:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_required_times_ate(t_philo_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == true && \
		node_th->times_must_eat == cnt)
		return (true);
	return (false);
}

void	count_ate_in_philo(t_philo_node *node_th)
{
	t_mutex				*mutex_struct;

	mutex_struct = &node_th->ph->mutex_struct;
	if (is_required_times_ate(node_th, node_th->cnt))
	{
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_th->ph->ate_struct.ate_cnt++;
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
}

// bool	is_ate_all(t_monitor_node *end_monitor)
// {
// 	pthread_mutex_t	*mutex_eat;

// 	mutex_eat = &end_monitor->eat_monitor.mutex_eat;
// 	if (end_monitor->ph->ate_struct.ate_all == true)
// 	{
// 		x_unlock_mutex(mutex_eat, end_monitor);
// 		return (true);
// 	}
// 	return (false);
// }



void	count_ate_person(t_philo_node *node_th)
{
	long	time_current;
	long	time_ate;
	long	timeval;
	long	time_to_eat;

	timeval = get_time_milli_sec();
	if (timeval < 0)
		node_th->flag_err = true;
	time_to_eat = node_th->ph->argv[3];
	time_current = timeval - node_th->start_time;
	time_ate = node_th->time[EATING] + time_to_eat;
	if (time_current > time_ate)
	{
		if (node_th->flag_wait_cnt == true)
		{
			node_th->cnt++;
			node_th->flag_wait_cnt = false;
		}
	}
}
