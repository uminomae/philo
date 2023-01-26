/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:11:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:27:52 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	free_alloc_ptr(t_ph *ph);
static bool	free_alloc_list_node(t_ph *ph);

bool	free_all(t_ph *ph)
{
	if (!free_alloc_ptr(ph))
		return (false);
	if (!free_alloc_list_node(ph))
		return (false);
	return (true);
}

static bool	free_alloc_ptr(t_ph *ph)
{
	t_ptr_node	*node;

	if (ph == NULL)
		return (false);
	if (ph->alloc_list.head == NULL)
		return (false);
	node = ph->alloc_list.head;
	while (node != NULL)
	{
		free(node->ptr);
		node = node->next;
	}
	return (true);
}

static bool	free_alloc_list_node(t_ph *ph)
{
	t_ptr_node	*node;
	t_ptr_node	*tmp;

	if (ph == NULL)
		return (false);
	if (ph->alloc_list.head == NULL)
		return (false);
	node = ph->alloc_list.head;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	return (true);
}
