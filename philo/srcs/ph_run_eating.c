/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_eating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/10 23:29:04 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	case_tail_person(t_pthread_node *node_th)
{
	if (node_th == node_th->ph->thread_list.tail)
		return (true);
	return (false);
}

static void	lock_mutex_forks(t_pthread_node *node_th, \
		t_fork_node *node_fork)
{
	t_fork_node		*node_next_fork;

	node_next_fork = node_fork->next;
	if (case_tail_person(node_th))
	{
		x_lock_mutex_fork(node_next_fork);
		x_lock_mutex_fork(node_fork);
	}
	else
	{
		x_lock_mutex_fork(node_fork);
		x_lock_mutex_fork(node_next_fork);
	}
}

static void	unlock_mutex_forks(t_pthread_node *node_th, \
		t_fork_node *node_fork)
{
	t_fork_node		*node_next_fork;

	node_next_fork = node_fork->next;
	if (case_tail_person(node_th))
	{
		x_unlock_mutex_fork(node_next_fork);
		x_unlock_mutex_fork(node_fork);
	}
	else
	{
		x_unlock_mutex_fork(node_fork);
		x_unlock_mutex_fork(node_next_fork);
	}
}

int	run_eating(t_pthread_node *node_th, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	lock_mutex_forks(node_th, node_fork);
	put_state(TAKEN_FORK, node_th, 0, id);
	put_state(EATING, node_th, time_eat, id);
	node_th->flag_wait_cnt = true;
	unlock_mutex_forks(node_th, node_fork);
	return (SUCCESS);
}
