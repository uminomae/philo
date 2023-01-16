/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/16 23:57:14 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static bool	case_tail_person(t_philo_node *node_th);
static void	unlock_mutex_forks(t_fork_node *node_fork);
static bool	lock_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id);
static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id);

void	*run_judge_hungry(void *ptr)
{
	t_philo_node	*node_philo;
	long	not_hungry_time;
	long	total;
	long	current;

	node_philo = (t_philo_node *)ptr;
	x_lock_mutex_philo(node_philo);
	not_hungry_time = node_philo->ph->argv[3] + node_philo->ph->argv[4];
	total = not_hungry_time + node_philo->time[EATING];
	x_unlock_mutex_philo(node_philo);
	if(!gettimeofday_millisec(node_philo->ph, &current))
		return (ptr);
	while(total > current)
	{
		if (total - current > 5)
		{
			if(!x_usleep_millisec(node_philo->ph, (total - current) / 2))
				return (ptr);
		}
		if(!gettimeofday_millisec(node_philo->ph, &current))
			return (ptr);
	}
	x_lock_mutex_philo(node_philo);
	node_philo->hungry = true;
	x_unlock_mutex_philo(node_philo);
	return (ptr);
}

bool	run_eating(t_philo_node *node_philo, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	while(1)
	{
		x_lock_mutex_philo(node_philo);
		if (node_philo->hungry == true)
		{
			x_unlock_mutex_philo(node_philo);
			break;
		}
		x_unlock_mutex_philo(node_philo);
	}
	if (!lock_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!lock_next_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!put_state(EATING, node_philo, time_eat, id))
	{
		unlock_mutex_forks(node_fork);
		return (false);
	}
	unlock_mutex_forks(node_fork);
	x_lock_mutex_philo(node_philo);
	node_philo->cnt++;
	node_philo->hungry = false;
	x_unlock_mutex_philo(node_philo);
	x_pthread_create(node_philo->ph, &node_philo->philo_monit_th, run_judge_hungry, node_philo);
	if(!x_pthread_detach(node_philo->ph, &node_philo->philo_monit_th))
		return (false);
	return (true);
}


static void	unlock_mutex_forks(t_fork_node *node_fork)
{
	t_fork_node		*node_next_fork;

	node_next_fork = node_fork->next;
	x_unlock_mutex_fork(node_next_fork);
	x_unlock_mutex_fork(node_fork);
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