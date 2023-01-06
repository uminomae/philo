/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:42:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 14:24:54 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork_node	*init_fork_node(t_ptr_list *ptr_list)
{
	t_fork_node	*node;

	node = (t_fork_node *)malloc_and_add_ptr_list(ptr_list, sizeof(t_fork_node));
	node->data = 0;
	node->next = NULL;
	return (node);
}

static void	make_first_fork_node(t_fork_list *list, t_fork_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_fork_node(t_fork_list *list, t_fork_node *node)
{
	list->tail->next = node;
	list->tail = node;
	node->next = list->head;
}

void	add_list(t_fork_list *list, t_ptr_list *ptr_list, size_t data)
{
	t_fork_node	*node;

	node = init_fork_node(ptr_list);
	node->data = data;
	if (list->head == NULL)
		make_first_fork_node(list, node);
	else
		add_last_fork_node(list, node);
}
