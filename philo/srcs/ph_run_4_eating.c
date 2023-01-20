/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:36:23 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	lock_fork_mutex(t_philo *node_philo, \
		t_fork_node *node_fork, t_fork_node *node_next_fork, size_t id);
static bool	lock_next_fork_mutex(t_philo *node_philo, \
		t_fork_node *node_fork, t_fork_node *node_next_fork, size_t id);

static void	unlock_next_fork(t_philo *node_philo, \
		t_fork_node *node_fork, t_fork_node *node_next_fork)
{
	if (node_philo->id % 2 == 0)
		x_unlock_mutex_fork(node_next_fork);
	else
		x_unlock_mutex_fork(node_fork);
}

bool	run_eating(t_philo *node_philo, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	t_fork_node	*node_next_fork;

	x_lock_mutex_fork(node_fork);
	node_next_fork = node_fork->next;
	x_unlock_mutex_fork(node_fork);
	if (!lock_fork_mutex(node_philo, node_fork, node_next_fork, id))
		return (false);
	if (!lock_next_fork_mutex(node_philo, node_fork, node_next_fork, id))
	{
		unlock_next_fork(node_philo, node_fork, node_next_fork);
		return (false);
	}
	if (!put_state(EATING, node_philo, time_eat, id))
	{
		x_unlock_mutex_fork(node_fork);
		x_unlock_mutex_fork(node_next_fork);
		return (false);
	}
	x_unlock_mutex_fork(node_fork);
	x_unlock_mutex_fork(node_next_fork);
	x_lock_mutex_philo(node_philo);
	node_philo->cnt++;
	x_unlock_mutex_philo(node_philo);
	return (true);
}

static bool	lock_fork_mutex(t_philo *node_philo, \
		t_fork_node *node_fork, t_fork_node *node_next_fork, size_t id)
{
	if (node_philo->id % 2 == 0)
	{
		x_lock_mutex_fork(node_next_fork);
		if (!put_state(TAKEN_FORK, node_philo, 0, id))
		{
			x_unlock_mutex_fork(node_next_fork);
			return (false);
		}
	}
	else
	{
		x_lock_mutex_fork(node_fork);
		if (!put_state(TAKEN_FORK, node_philo, 0, id))
		{
			x_unlock_mutex_fork(node_fork);
			return (false);
		}
	}
	return (true);
}

static bool	lock_next_fork_mutex(t_philo *node_philo, \
		t_fork_node *node_fork, t_fork_node *node_next_fork, size_t id)
{
	if (node_philo->id % 2 == 0)
	{
		x_lock_mutex_fork(node_fork);
		if (!put_state(TAKEN_FORK, node_philo, 0, id))
		{
			x_unlock_mutex_fork(node_fork);
			return (false);
		}
	}
	else
	{
		x_lock_mutex_fork(node_next_fork);
		if (!put_state(TAKEN_FORK, node_philo, 0, id))
		{
			x_unlock_mutex_fork(node_next_fork);
			return (false);
		}
	}
	return (true);
}
