/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_list_pthread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:50:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 14:47:18 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_pthread_node	*init_pthread_node(t_ptr_list *ptr_list)
{
	t_pthread_node	*node;

	node = (t_pthread_node *)malloc_and_add_ptr_list(ptr_list, \
				sizeof(t_pthread_node));
	// node->thread = NULL;
	node->next = NULL;
	return (node);
}

static void	make_first_pthread_node(t_pthread_list *list, t_pthread_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_pthread_node(t_pthread_list *list, t_pthread_node *node)
{
	list->tail->next = node;
	list->tail = node;
	node->next = list->head;
}

void set_status_to_thread_list(t_philo *ph, t_pthread_node *node)
{
	size_t	i;

	i = 0;
	while (i < PUT_TYPE_END)
	{
		node->status[i] = &ph->status[i];
		i++;
	}
}

void	add_pthread_list( \
			t_philo *ph, t_pthread_list *list, t_ptr_list *ptr_list, size_t id)
{
	t_pthread_node	*node_th;

	node_th = init_pthread_node(ptr_list);
	node_th->id = id;
	node_th->ph = ph;
	set_status_to_thread_list(ph, node_th);
	if (list->head == NULL)
		make_first_pthread_node(list, node_th);
	else
		add_last_pthread_node(list, node_th);
}
