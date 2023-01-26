/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_list_fork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:42:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:46:16 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork	*init_fork(t_ptr_list *ptr_list);
static void		make_first_fork(t_fork_list *list, t_fork *node);
static void		add_last_fork(t_fork_list *list, t_fork *node);

bool	add_fork_list(t_ph *ph, t_fork_list *fork_list, \
					t_ptr_list *ptr_list, size_t data)
{
	t_fork	*fork_n;

	fork_n = init_fork(ptr_list);
	if (fork_n == NULL)
	{
		set_err_num_ph(ph, ERR_ADD_FORK_LIST);
		return (false);
	}
	fork_n->data = data;
	fork_n->ph = ph;
	if (fork_list->head == NULL)
		make_first_fork(fork_list, fork_n);
	else
		add_last_fork(fork_list, fork_n);
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
