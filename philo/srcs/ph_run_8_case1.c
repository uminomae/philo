/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_8_case1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 11:23:42 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	run_case_1person(t_philo_node *node_philo, t_fork_node *node_fork)
{
	// long time;

	x_lock_mutex_fork(node_fork);
	if (!put_state(TAKEN_FORK, node_philo, 0, node_philo->id))
	{
		x_unlock_mutex_fork(node_fork);
		return ;
	}
	x_unlock_mutex_fork(node_fork);
	usleep(node_philo->ph->argv[2] * 1000);
	x_lock_mutex_philo(node_philo);
	set_flag_died(node_philo->ph, node_philo->id);
	x_unlock_mutex_philo(node_philo);
	// if (node_philo->ph->died_struct.died_flag)
	// {
	// 	if (!gettimeofday_millisec(node_philo->ph, &time))
	// 		return ;
	// 	put_stamp(time, node_philo->ph->died_struct.died_id, DIED_STR);
	// }
	return ;
}
