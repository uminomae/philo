/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_eating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 09:36:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	case_tail_person(t_philo_node *node_th)
{
	if (node_th == node_th->ph->philo_list.tail)
		return (true);
	return (false);
}

static void	lock_mutex_forks(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id)
{
	t_fork_node		*node_next_fork;

	node_next_fork = node_fork->next;
	if (case_tail_person(node_philo))
	{
		x_lock_mutex_fork(node_next_fork);
		put_state(TAKEN_FORK, node_philo, 0, id);
		x_lock_mutex_fork(node_fork);
		put_state(TAKEN_FORK, node_philo, 0, id);
	}
	else
	{
		x_lock_mutex_fork(node_fork);
		put_state(TAKEN_FORK, node_philo, 0, id);
		x_lock_mutex_fork(node_next_fork);
		put_state(TAKEN_FORK, node_philo, 0, id);
	}
}

static void	unlock_mutex_forks(t_philo_node *node_th, \
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

// wait見直す
int	run_eating(t_philo_node *node_philo, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	lock_mutex_forks(node_philo, node_fork, id);
	// put_state(TAKEN_FORK, node_philo, 0, id);
	x_lock_mutex_philo(node_philo);
	put_state(EATING, node_philo, time_eat, id);
	node_philo->flag_wait_cnt = true;
	x_unlock_mutex_philo(node_philo);
	unlock_mutex_forks(node_philo, node_fork);
	return (SUCCESS);
}
