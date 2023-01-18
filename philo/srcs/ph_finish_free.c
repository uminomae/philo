/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_finish_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:11:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 18:10:17 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	free_alloc_ptr(t_philo_main *ph);
bool	free_alloc_list_node(t_philo_main *ph);

bool	free_all(t_philo_main *ph)
{
	if (!free_alloc_ptr(ph))
		return (false);
	if (!free_alloc_list_node(ph))
		return (false);
	return (true);
}

bool	free_alloc_ptr(t_philo_main *ph)
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

bool	free_alloc_list_node(t_philo_main *ph)
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
