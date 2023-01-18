/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 20:27:46 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	count_ate_in_philo(t_philo_node *node_philo);
static void	unlock_both_mutex_forks( \
		t_fork_node *node_fork, t_fork_node *node_next_fork);
static bool	lock_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, t_fork_node *node_next_fork, size_t id);
static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, t_fork_node *node_next_fork, size_t id);

bool	run_eating(t_philo_node *node_philo, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	t_fork_node	*node_next_fork;

	x_lock_mutex_fork(node_fork);
	node_next_fork = node_fork->next;
	x_unlock_mutex_fork(node_fork);
	if (!lock_fork_mutex(node_philo, node_fork, node_next_fork, id))
		return (false);
	if (!lock_next_fork_mutex(node_philo, node_fork, node_next_fork, id))
		return (false);
	// return (false);//TODO
	if (!put_state(EATING, node_philo, time_eat, id))
	{
		unlock_both_mutex_forks(node_fork, node_next_fork);
		return (false);
	}
	unlock_both_mutex_forks(node_fork, node_next_fork);
	x_lock_mutex_philo(node_philo);
	node_philo->cnt++;
	x_unlock_mutex_philo(node_philo);
	if (node_philo->ph->flag_must_eat == true)
		count_ate_in_philo(node_philo);
	return (true);
}

static void	count_ate_in_philo(t_philo_node *node_philo)
{
	t_mutex	*mutex_struct;

	mutex_struct = &node_philo->ph->mutex_struct;
	x_lock_mutex_philo(node_philo);
	if (node_philo->times_must_eat == node_philo->cnt)
	{
		x_unlock_mutex_philo(node_philo);
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
	x_unlock_mutex_philo(node_philo);
}

static void	unlock_both_mutex_forks( \
		t_fork_node *node_fork, t_fork_node *node_next_fork)
{
	x_unlock_mutex_fork(node_fork);
	x_unlock_mutex_fork(node_next_fork);
}

static bool	lock_fork_mutex(t_philo_node *node_philo, \
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

static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
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
