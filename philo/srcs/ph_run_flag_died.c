/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_flag_died.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/10 22:15:56 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_flag_died(t_philo *ph, t_pthread_node *node_th)
{
	x_lock_mutex(&ph->end_monitor.die_monitor.mutex_die, &ph->end_monitor.eat_monitor);
	ph->end_monitor.die_monitor.flag_died = true;
	ph->end_monitor.die_monitor.died_id = node_th->id;
	x_unlock_mutex(&ph->end_monitor.die_monitor.mutex_die, &ph->end_monitor.eat_monitor);
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

bool	is_flag_died(t_pthread_monitor *end_monitor)
{
	bool			ret;
	t_eat_monitor	*eat_monitor;
	t_die_monitor	*die_monitor;

	ret = false;
	eat_monitor = &end_monitor->eat_monitor;
	x_lock_mutex(&end_monitor->die_monitor.mutex_die, eat_monitor);
	die_monitor = &end_monitor->die_monitor;
	if (die_monitor->flag_died == true)
		ret = true;
	x_unlock_mutex(&end_monitor->die_monitor.mutex_die, eat_monitor);
	return (ret);
}


