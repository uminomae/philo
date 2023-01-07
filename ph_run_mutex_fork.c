/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_mutex_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/07 19:34:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_mutex(t_fork_node *node)
{
	int	ret;

	ret = pthread_mutex_lock(&node->mutex);
	if (ret != 0)
		get_err_flag_node_fork(node);
}

void	unlock_mutex(t_fork_node *node)
{
	int	ret;

	ret = pthread_mutex_unlock(&node->mutex);
	if (ret != 0)
		get_err_flag_node_fork(node);
}

void	lock_mutex_monitor(t_monitor *monitor)
{
	int	ret;

	ret = pthread_mutex_lock(&monitor->mutex);
	if (ret != 0)
		get_err_flag_monitor(monitor);
}

void	unlock_mutex_monitor(t_monitor *monitor)
{
	int	ret;

	ret = pthread_mutex_unlock(&monitor->mutex);
	if (ret != 0)
		get_err_flag_monitor(monitor);
}

t_fork_node	*get_fork_node(t_fork_list *list, size_t c)
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
void	toggle_mutex_forks(size_t flag, t_fork_node *node_fork)
// void	toggle_mutex_forks(size_t flag, t_pthread_node *node_th, t_fork_node *node_fork, size_t id)
{

	if (flag == LOCK)
	{
		lock_mutex(node_fork);
		lock_mutex(node_fork->next);
	}
	else if (flag == UNLOCK)
	{
		unlock_mutex(node_fork->next);
		unlock_mutex(node_fork);
	}
}
