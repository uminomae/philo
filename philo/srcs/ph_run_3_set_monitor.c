/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_set_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 11:30:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_and_run_pthread_monitor(t_monitor_node *node_monitor)
{
	int	ret;

	ret = pthread_create(&node_monitor->monitor_th, NULL, run_rutine_monitor_in_thread, node_monitor);
	if (ret != 0)
		get_err_flag_eat_monitor(&node_monitor->eat_monitor);
}

void	set_and_run_monitor(t_philo_main *ph, size_t id)
{
	t_monitor_node	*node_monitor;

	node_monitor = get_monitor_node(&ph->monitor_list, id);
	node_monitor->id = id;
	// printf("set monitor ------------- %ld\n", id);
	node_monitor->start_time = ph->start_time;
	node_monitor->flag_must_eat = ph->flag_must_eat;
	node_monitor->times_must_eat = ph->argv[5];
	node_monitor->mutex_struct = &ph->mutex_struct;
	node_monitor->ate_struct = &ph->ate_struct;
	node_monitor->died_struct = &ph->died_struct;
	// printf("set monitor ------------- %p\n", node_monitor->mutex_struct);
	// printf("set monitor ------------- %p\n", node_monitor->ate_struct);
	// printf("set monitor ------------- %p\n", node_monitor->died_struct);
	create_and_run_pthread_monitor(node_monitor);
}
