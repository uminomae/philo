/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_list_fork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:42:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:37:23 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork	*init_fork(t_ptr_list *ptr_list);
static void			make_first_fork(t_fork_list *list, t_fork *node);
static void			add_last_fork(t_fork_list *list, t_fork *node);

bool	add_fork_list(t_ph *ph, t_fork_list *list, \
					t_ptr_list *ptr_list, size_t data)
{
	t_fork	*node;

	node = init_fork(ptr_list);
	if (node == NULL)
	{
		get_err_num_ph(ph, ERR_ADD_FORK_LIST);
		return (false);
	}
	node->data = data;
	node->ph = ph;
	if (list->head == NULL)
		make_first_fork(list, node);
	else
		add_last_fork(list, node);
	return (true);
}

static t_fork	*init_fork(t_ptr_list *ptr_list)
{
	t_fork	*node;

	node = (t_fork *)malloc_and_add_ptr_list(ptr_list, \
				sizeof(t_fork));
	if (node == NULL)
		return (NULL);
	memset(node, 0, sizeof(t_fork));
	return (node);
}

static void	make_first_fork(t_fork_list *list, t_fork *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_fork(t_fork_list *list, t_fork *node)
{
	list->tail->next = node;
	list->tail = node;
	node->next = list->head;
}
