/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_set_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 21:11:40 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_and_run_pthread_monitor(t_monitor_node *node_monitor);

void	set_and_run_monitor(t_philo_main *ph, size_t id)
{
	t_monitor_node	*node_monitor;

	node_monitor = get_monitor_node(&ph->monitor_list, id);
	node_monitor->flag_must_eat = ph->flag_must_eat;
	node_monitor->times_must_eat = ph->argv[5];
	create_and_run_pthread_monitor(node_monitor);
}

static void	create_and_run_pthread_monitor(t_monitor_node *node_monitor)
{
	int	ret;

	ret = pthread_create(&node_monitor->monitor_th, NULL, run_rutine_monitor_in_thread, node_monitor);
	if (ret != 0)
		get_err_num_ph(node_monitor->ph, ERR_PTHREAD_CREATE);
}
