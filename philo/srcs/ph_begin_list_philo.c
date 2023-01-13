/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_list_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:50:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 11:57:54 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo_node	*init_philo_node(t_ptr_list *ptr_list)
{
	t_philo_node	*node;

	node = (t_philo_node *)malloc_and_add_ptr_list(ptr_list, \
				sizeof(t_philo_node));
	if (node == NULL)
		return (NULL);
	memset(node, 0, sizeof(t_philo_node));
	return (node);
}

static void	make_first_philo_node(t_philo_list *list, t_philo_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_philo_node(t_philo_list *list, t_philo_node *node)
{
	list->tail->next = node;
	list->tail = node;
	node->next = list->head;
}

// static void	set_status_to_thread_list(t_philo_main *ph, t_philo_node *node)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < PUT_TYPE_END)
// 	{
// 		node->status[i] = ph->status[i];
// 		// printf("%s\n", *node->status[i]);
// 		i++;
// 	}
// }

size_t	add_philo_list( \
			t_philo_main *ph, t_philo_list *list, t_ptr_list *ptr_list, size_t id)
{
	t_philo_node	*node_th;

	node_th = init_philo_node(ptr_list);
	if (node_th == NULL)
		return (1);
	node_th->id = id;
	node_th->ph = ph;
	// set_status_to_thread_list(ph, node_th);
	if (list->head == NULL)
		make_first_philo_node(list, node_th);
	else
		add_last_philo_node(list, node_th);
	return (0);
}
