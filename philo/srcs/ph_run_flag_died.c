/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_flag_died.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 19:08:25 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_flag_died(t_philo_main *ph, t_philo_node *node_th)
{
	t_mutex			*mutex_struct;

	mutex_struct = &ph->mutex_struct;
	x_lock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
	ph->died_struct.died_flag = true;
	ph->died_struct.died_id = node_th->id;
	x_unlock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
	node_th->flag_died = true;
}

bool	check_time_to_die(t_philo_node *node_th, long time_current)
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

bool	is_flag_died(t_pthread_monitor_node *end_monitor)
{
	bool			ret;
	t_die_struct	*died_struct;
	t_mutex			*mutex_struct;

	mutex_struct = &end_monitor->ph->mutex_struct;
	died_struct = &end_monitor->ph->died_struct;
	ret = false;
	x_lock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
	if (died_struct->died_flag == true)
		ret = true;
	x_unlock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
	return (ret);
}


