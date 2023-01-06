/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 14:04:57 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_mutex(t_fork_node *node)
{
	int	ret;

	ret = pthread_mutex_lock(&node->mutex);
	if (ret != 0)
		exit(1);
}

static void	unlock_mutex(t_fork_node *node)
{
	int	ret;

	ret = pthread_mutex_unlock(&node->mutex);
	if (ret != 0)
		exit(1);
}

static t_fork_node	*get_fork_node(t_list *list, size_t c)
{
	size_t	i;
	t_fork_node	*node;

	node = list->head;
	i = 0;
	while (i < c)
	{
		node = node->next;
		i++;
	}
	return (node);
}

// //unlock_mutex(node_fork->next);を先にしている
void	toggle_mutex_forks(t_pthread_node *node_th, t_list *list_fork, size_t id, size_t flag)
{
	t_fork_node	*node_fork;

	node_fork = get_fork_node(list_fork, id);
	if (flag == TRUE)
	{
		lock_mutex(node_fork);
		change_state_philosopher(TAKEN_FORK, node_th, 0, id);
		// run_taken_fork(node_th, id);
		lock_mutex(node_fork->next);
	}
	else if (flag == FALSE)
	{
		unlock_mutex(node_fork->next);
		unlock_mutex(node_fork);
	}
}
