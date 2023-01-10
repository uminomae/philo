/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_flag_ate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/10 22:13:47 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == true && \
		node_th->times_must_eat == cnt)
		return (true);
	return (false);
}

void	count_ate_in_mutex_monitor(t_pthread_node *node_th)
{
	pthread_mutex_t	*mutex_eat;
	t_eat_monitor	*eat_monitor;

	mutex_eat = &node_th->ph->end_monitor.eat_monitor.mutex_eat;
	eat_monitor = &node_th->ph->end_monitor.eat_monitor;
	if (is_required_times_ate(node_th, node_th->cnt))
	{
		x_lock_mutex(mutex_eat, eat_monitor);
		node_th->ph->end_monitor.eat_monitor.ate_cnt++;
		x_unlock_mutex(mutex_eat, eat_monitor);
	}
}

bool	is_ate_all(t_eat_monitor *eat_monitor)
{
	if (eat_monitor->ate_all == true)
	{
		x_unlock_mutex(&eat_monitor->mutex_eat, eat_monitor);
		return (true);
	}
	return (false);
}

bool	judge_ate_all(t_eat_monitor *eat_monitor, size_t num_people)
{
	if (eat_monitor->ate_cnt == num_people)
	{
		eat_monitor->ate_all = true;
		x_unlock_mutex(&eat_monitor->mutex_eat, eat_monitor);
		return (true);
	}
	return (false);
}

void	count_ate_person(t_pthread_node *node_th)
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
