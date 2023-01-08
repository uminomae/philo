/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_flag_died.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 04:46:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_flag_died(t_philo *ph, t_pthread_node *node_th)
{
	x_lock_mutex(&ph->die_monitor.mutex_die, &ph->monitor);
	ph->die_monitor.time_died = get_time_milli_sec() - node_th->start_time;
	if (ph->die_monitor.time_died < 0)
		get_err_flag(ph);
	ph->die_monitor.flag_died = true;
	ph->die_monitor.died_id = node_th->id;
	x_unlock_mutex(&ph->die_monitor.mutex_die, &ph->monitor);
	node_th->flag_died = true;
}

bool	check_time_to_die(t_pthread_node *node_th, long time_current)
{
	long	start;
	long	eating;
	long	time_to_eat;

	start = node_th->start_time;
	eating = node_th->time[EATING];
	time_to_eat = (long)node_th->ph->argv[2];
	if (time_current - (start + eating) >= time_to_eat)
	{
		set_flag_died(node_th->ph, node_th);
		return (true);
	}
	return (false);
}

bool	is_flag_died(t_pthread_node *node_th)
{
	bool			ret;
	pthread_mutex_t	*mutex_died;
	t_eat_monitor		*monitor;
	t_die_monitor	*die_monitor;

	mutex_died = &node_th->ph->die_monitor.mutex_die;
	monitor = &node_th->ph->monitor;
	die_monitor = &node_th->ph->die_monitor;
	ret = false;
	x_lock_mutex(mutex_died, monitor);
	if (die_monitor->flag_died == true)
		ret = true;
	x_unlock_mutex(mutex_died, monitor);
	return (ret);
}

void	count_ate_in_mutex_monitor(t_pthread_node *node_th)
{
	pthread_mutex_t	*mutex_eat;
	t_eat_monitor		*monitor;

	mutex_eat = &node_th->ph->monitor.mutex_eat;
	monitor = &node_th->ph->monitor;
	if (is_required_times_ate(node_th, node_th->cnt))
	{
		x_lock_mutex(mutex_eat, monitor);
		node_th->ph->monitor.ate_cnt++;
		x_unlock_mutex(mutex_eat, monitor);
	}
}


bool	judge_ate_died(t_pthread_node *node_th)
{
	pthread_mutex_t	*mutex_eat;
	t_eat_monitor		*monitor;

	mutex_eat = &node_th->ph->monitor.mutex_eat;
	monitor = &node_th->ph->monitor;
	count_ate_person(node_th);
	if (check_time_to_die(node_th, get_time_milli_sec()))
		return (true);
	if (is_flag_died(node_th))
		return (true);
	count_ate_in_mutex_monitor(node_th);
	x_lock_mutex(mutex_eat, monitor);
	if (is_ate_all(monitor))
		return (true);
	x_unlock_mutex(mutex_eat, monitor);
	x_lock_mutex(mutex_eat, monitor);
	if (judge_ate_all(monitor, node_th->ph->argv[1]))
		return (true);
	x_unlock_mutex(mutex_eat, monitor);
	return (false);
}
