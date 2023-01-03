/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:42:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/04 00:42:53 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_node	*init_node(t_ptr_list *ptr_list)
{
	t_node	*node;

	node = (t_node *)malloc_and_add_ptr_list(ptr_list, sizeof(t_node));
	node->data = 0;
	node->next = NULL;
	return (node);
}

static void	make_first_node(t_list *list, t_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_node(t_list *list, t_node *node)
{
	list->tail->next = node;
	list->tail = node;
	node->next = list->head;
}

void	add_list(t_list *list, t_ptr_list *ptr_list, size_t data)
{
	t_node	*node;

	node = init_node(ptr_list);
	node->data = data;
	if (list->head == NULL)
		make_first_node(list, node);
	else
		add_last_node(list, node);
}
