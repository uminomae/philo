/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_is_died.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 20:45:55 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	set_flag_died(t_philo_main *ph, size_t id)
// {
// 	t_mutex			*mutex_struct;

// 	mutex_struct = &ph->mutex_struct;

// 	x_lock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);
// 	ph->died_struct.died_flag = true;
// 	ph->died_struct.died_id = id;
// 	x_unlock_mutex_struct(&mutex_struct->mutex_die ,mutex_struct);

// 	x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
// 	ph->end_struct.flag_end = true;
// 	x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
// }

// bool	check_time_to_die(t_philo_node *node_philo, long time_current)
// {
// 	const long	start = node_philo->start_time;
// 	const long	eating = node_philo->time[EATING];
// 	const long	time_to_eat = (long)node_philo->ph->argv[2];
	
// 	if (time_current - (start + eating) >= time_to_eat)
// 	{
// 		set_flag_died(node_philo->ph, node_philo->id);
// 		return (true);
// 	}
// 	return (false);
// }
