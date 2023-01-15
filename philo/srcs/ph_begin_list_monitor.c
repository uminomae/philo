/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_list_monitor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:50:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/14 23:41:50 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static t_monitor_node	*init_monitor_node(t_ptr_list *ptr_list);
// static void	make_first_monitor_node(t_monitor_list *list, t_monitor_node *node);
// static void	add_last_monitor_node(t_monitor_list *list, t_monitor_node *node);

// size_t	add_monitor_list( \
// 			t_philo_main *ph, t_monitor_list *monitor_list, t_ptr_list *ptr_list, size_t id)
// {
// 	t_monitor_node	*node_monitor;

// 	node_monitor = init_monitor_node(ptr_list);
// 	if (node_monitor == NULL)
// 		return (1);
// 	node_monitor->ph = ph;
// 	node_monitor->node_philo = get_philo_node(&ph->philo_list, id);
// 	if (monitor_list->head == NULL)
// 		make_first_monitor_node(monitor_list, node_monitor);
// 	else
// 		add_last_monitor_node(monitor_list, node_monitor);
// 	return (0);
// }

// static t_monitor_node	*init_monitor_node(t_ptr_list *ptr_list)
// {
// 	t_monitor_node	*node;

// 	node = (t_monitor_node *)malloc_and_add_ptr_list(ptr_list, \
// 				sizeof(t_monitor_node));
// 	if (node == NULL)
// 		return (NULL);
// 	memset(node, 0, sizeof(t_monitor_node));
// 	return (node);
// }

// static void	make_first_monitor_node(t_monitor_list *list, t_monitor_node *node)
// {
// 	list->head = node;
// 	list->tail = node;
// }

// static void	add_last_monitor_node(t_monitor_list *list, t_monitor_node *node)
// {
// 	list->tail->next = node;
// 	list->tail = node;
// 	node->next = list->head;
// }
