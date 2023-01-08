/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_flag_died.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 04:19:36 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_flag_died(t_philo *ph, t_pthread_node *node_th)
{
	x_lock_mutex(&ph->die_monitor.mutex, &ph->monitor);
	ph->die_monitor.time_died = get_time_milli_sec() - node_th->start_time;
	ph->die_monitor.flag_died = true;
	ph->die_monitor.died_id = node_th->id;
	x_unlock_mutex(&ph->die_monitor.mutex, &ph->monitor);
	node_th->flag_died = true;
}

bool	check_time_to_die(t_pthread_node *node_th, long time_current)
{
	if (time_current - (node_th->start_time + \
		node_th->time[EATING]) >= (long)node_th->ph->argv[2])
	{
		set_flag_died(node_th->ph, node_th);
		return (true);
	}
	return (false);
}

bool	is_flag_died(t_pthread_node *node_th)
{
	bool	ret;

	ret = false;
	x_lock_mutex(&node_th->ph->die_monitor.mutex, \
			&node_th->ph->monitor);
	if (node_th->ph->die_monitor.flag_died == true)
		ret = true;
	x_unlock_mutex(&node_th->ph->die_monitor.mutex, \
			&node_th->ph->monitor);
	return (ret);
}

void	count_ate_in_mutex_monitor(t_pthread_node *node_th)
{
	if (is_required_times_ate(node_th, node_th->cnt))
	{
		x_lock_mutex(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
		node_th->ph->monitor.ate_cnt++;
		x_unlock_mutex(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	}
}


bool	judge_ate_died(t_pthread_node *node_th)
{
	
	count_ate_person(node_th);
	if (check_time_to_die(node_th, get_time_milli_sec()))
		return (true);
	if (is_flag_died(node_th))
		return (true);
	count_ate_in_mutex_monitor(node_th);

	x_lock_mutex(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	if (is_ate_all(&node_th->ph->monitor))
		return (true);
	x_unlock_mutex(&node_th->ph->monitor.mutex, &node_th->ph->monitor);

	x_lock_mutex(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	if (judge_ate_all(&node_th->ph->monitor, node_th->ph->argv[1]))
		return (true);
	x_unlock_mutex(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	return (false);
}
