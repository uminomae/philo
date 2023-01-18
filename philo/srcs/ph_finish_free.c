/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_finish_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:11:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 16:52:51 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_alloc_ptr(t_philo_main *ph);
void	free_alloc_list_node(t_philo_main *ph);

void	free_all(t_philo_main *ph)
{
	free_alloc_ptr(ph);
	free_alloc_list_node(ph);
}

void	free_alloc_ptr(t_philo_main *ph)
{
	t_ptr_node	*node;

	if (ph == NULL)
		return ;
	if (ph->alloc_list.head == NULL)
		return ;
	node = ph->alloc_list.head;
	while (node != NULL)
	{
		free(node->ptr);
		node = node->next;
	}
}

void	free_alloc_list_node(t_philo_main *ph)
{
	t_ptr_node	*node;
	t_ptr_node	*tmp;

	if (ph == NULL)
		return ;
	if (ph->alloc_list.head == NULL)
		return ;
	node = ph->alloc_list.head;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
}
