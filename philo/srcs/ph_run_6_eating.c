/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_6_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 11:57:41 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	case_tail_person(t_philo_node *node_th)
{
	if (node_th == node_th->ph->philo_list.tail)
		return (true);
	return (false);
}

static void	unlock_mutex_forks(t_philo_node *node_philo, \
		t_fork_node *node_fork)
{
	t_fork_node		*node_next_fork;

	node_next_fork = node_fork->next;
	if (case_tail_person(node_philo))
	{
		x_unlock_mutex_fork(node_fork);
		x_unlock_mutex_fork(node_next_fork);
	}
	else
	{
		x_unlock_mutex_fork(node_next_fork);
		x_unlock_mutex_fork(node_fork);
	}
}

static bool	lock_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id)
{
	t_fork_node	*node_next_fork;

	x_lock_mutex_fork(node_fork);
	node_next_fork = node_fork->next;
	x_unlock_mutex_fork(node_fork);
	if (case_tail_person(node_philo))
	{
		x_lock_mutex_fork(node_next_fork);
		if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		{
			x_unlock_mutex_fork(node_next_fork);
			return (false);
		}
	}
	else
	{
		x_lock_mutex_fork(node_fork);
		if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		{
			x_unlock_mutex_fork(node_fork);
			return (false);
		}
	}
	put_state(TAKEN_FORK, node_philo, 0, id);
	return (true);
}

static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id)
{
	t_fork_node	*node_next_fork;

	node_next_fork = node_fork->next;
	if (case_tail_person(node_philo))
	{
		x_lock_mutex_fork(node_fork);
		if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		{
			x_unlock_mutex_fork(node_fork);
			return (false);
		}
	}
	else
	{
		x_lock_mutex_fork(node_next_fork);
		if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		{
			x_unlock_mutex_fork(node_next_fork);
			return (false);
		}
	}
	put_state(TAKEN_FORK, node_philo, 0, id);
	return (true);
}

bool	run_eating(t_philo_node *node_philo, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	if (!lock_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!lock_next_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
	{
		x_lock_mutex_philo(node_philo);
		put_state(EATING, node_philo, time_eat, id);
		node_philo->cnt++;
		x_unlock_mutex_philo(node_philo);
	}	
	unlock_mutex_forks(node_philo, node_fork);
	return (true);
}
