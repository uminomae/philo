/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 00:24:04 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool is_hungry(t_philo_node *node_philo);
static void	unlock_both_mutex_forks(t_fork_node *node_fork);
static bool	lock_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id);
static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id);

bool	run_eating(t_philo_node *node_philo, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	while(!is_hungry(node_philo));
	if (!lock_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!lock_next_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!put_state(EATING, node_philo, time_eat, id))
	{
		unlock_both_mutex_forks(node_fork);
		return (false);
	}
	unlock_both_mutex_forks(node_fork);
	x_lock_mutex_philo(node_philo);
	node_philo->cnt++;
	node_philo->hungry = false;
	x_unlock_mutex_philo(node_philo);
	x_pthread_create(node_philo->ph, &node_philo->philo_monit_th, run_judge_hungry, node_philo);
	if(!x_pthread_detach(node_philo->ph, &node_philo->philo_monit_th))
		return (false);
	return (true);
}

static bool is_hungry(t_philo_node *node_philo)
{
	x_lock_mutex_philo(node_philo);
	if (node_philo->hungry == true)
	{
		x_unlock_mutex_philo(node_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_philo);
	return (false);
}

static bool	lock_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id)
{

	x_lock_mutex_fork(node_fork);
	if (!put_state(TAKEN_FORK, node_philo, 0, id))
	{
		x_unlock_mutex_fork(node_fork);
		return (false);
	}
	return (true);
}

static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id)
{
	t_fork_node	*node_next_fork;

	node_next_fork = node_fork->next;
	x_lock_mutex_fork(node_next_fork);
	if (!put_state(TAKEN_FORK, node_philo, 0, id))
	{
		x_unlock_mutex_fork(node_next_fork);
		return (false);
	}
	return (true);
}

static void	unlock_both_mutex_forks(t_fork_node *node_fork)
{
	t_fork_node		*node_next_fork;

	node_next_fork = node_fork->next;
	x_unlock_mutex_fork(node_next_fork);
	x_unlock_mutex_fork(node_fork);
}
