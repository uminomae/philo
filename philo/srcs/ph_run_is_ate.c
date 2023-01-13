/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_is_ate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 16:45:51 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_finished_ate_last_person(t_philo_node *node_th)
// {
// 	long	time_current;
// 	long	time_ate;
// 	long	timeval;
// 	long	time_to_eat;

// 	timeval = get_time_milli_sec();
// 	if (timeval < 0)
// 		node_th->flag_err = true;
// 	time_to_eat = node_th->ph->argv[3];
// 	time_current = timeval - node_th->start_time;
// 	time_ate = node_th->time[EATING] + time_to_eat;
// 	if (time_current > time_ate)
// 	{
// 		return (true);
// 		// if (node_th->flag_wait_ate == true)
// 		// {
// 		// 	// node_th->cnt++;
// 		// 	node_th->flag_wait_ate = false;
// 		// }
// 	}
// 	return (false);
// }
