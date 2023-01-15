/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_list_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:50:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 00:38:12 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo_node	*init_philo_node(t_ptr_list *ptr_list);
static void	make_first_philo_node(t_philo_list *list, t_philo_node *node);
static void	add_last_philo_node(t_philo_list *list, t_philo_node *node);

size_t	add_philo_list( \
			t_philo_main *ph, t_philo_list *list, t_ptr_list *ptr_list, size_t id)
{
	t_philo_node	*node_philo;

	node_philo = init_philo_node(ptr_list);
	if (node_philo == NULL)
		return (1);
	node_philo->id = id;
	node_philo->ph = ph;
	node_philo->mutex_struct = &ph->mutex_struct;
	if (list->head == NULL)
		make_first_philo_node(list, node_philo);
	else
		add_last_philo_node(list, node_philo);
	return (0);
}

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
