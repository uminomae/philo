/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_philo_eating.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:50:05 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	lock_fork_mutex(t_philo *philo_n, \
				t_fork *fork_n, t_fork *next_fork_n, size_t id);
static bool	lock_next_fork_mutex(t_philo *philo_n, \
				t_fork *fork_n, t_fork *next_fork_n, size_t id);

static void	unlock_next_fork(t_philo *philo_n, \
				t_fork *fork_n, t_fork *next_fork_n)
{
	if (philo_n->id % 2 == 0)
		x_unlock_mutex_fork(next_fork_n);
	else
		x_unlock_mutex_fork(fork_n);
}

bool	run_eating(t_philo *philo_n, t_fork *fork_n, size_t id, long time_eat)
{
	t_fork	*next_fork_n;

	x_lock_mutex_fork(fork_n);
	next_fork_n = fork_n->next;
	x_unlock_mutex_fork(fork_n);
	if (!lock_fork_mutex(philo_n, fork_n, next_fork_n, id))
		return (false);
	if (!lock_next_fork_mutex(philo_n, fork_n, next_fork_n, id))
	{
		unlock_next_fork(philo_n, fork_n, next_fork_n);
		return (false);
	}
	if (!put_state(EATING, philo_n, time_eat, id))
	{
		x_unlock_mutex_fork(fork_n);
		x_unlock_mutex_fork(next_fork_n);
		return (false);
	}
	x_unlock_mutex_fork(fork_n);
	x_unlock_mutex_fork(next_fork_n);
	x_lock_mtx_philo(philo_n, &philo_n->mtx_philo);
	philo_n->cnt++;
	x_unlock_mtx_philo(philo_n, &philo_n->mtx_philo);
	return (true);
}

static bool	lock_fork_mutex(t_philo *philo_n, \
				t_fork *fork_n, t_fork *next_fork_n, size_t id)
{
	if (philo_n->id % 2 == 0)
	{
		x_lock_mutex_fork(next_fork_n);
		if (!put_state(TAKEN_FORK, philo_n, 0, id))
		{
			x_unlock_mutex_fork(next_fork_n);
			return (false);
		}
	}
	else
	{
		x_lock_mutex_fork(fork_n);
		if (!put_state(TAKEN_FORK, philo_n, 0, id))
		{
			x_unlock_mutex_fork(fork_n);
			return (false);
		}
	}
	return (true);
}

static bool	lock_next_fork_mutex(t_philo *philo_n, \
				t_fork *fork_n, t_fork *next_fork_n, size_t id)
{
	if (philo_n->id % 2 == 0)
	{
		x_lock_mutex_fork(fork_n);
		if (!put_state(TAKEN_FORK, philo_n, 0, id))
		{
			x_unlock_mutex_fork(fork_n);
			return (false);
		}
	}
	else
	{
		x_lock_mutex_fork(next_fork_n);
		if (!put_state(TAKEN_FORK, philo_n, 0, id))
		{
			x_unlock_mutex_fork(next_fork_n);
			return (false);
		}
	}
	return (true);
}
