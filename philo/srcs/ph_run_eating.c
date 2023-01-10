/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_eating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 19:52:17 by uminomae         ###   ########.fr       */
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
		t_fork_node *node_fork, t_eat_monitor *eat_monitor)
{
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		*mutex_next_fork;

	mutex_fork = &node_fork->mutex_fork;
	mutex_next_fork = &node_fork->next->mutex_fork;
	if (case_tail_person(node_th))
	{
		x_lock_mutex(mutex_next_fork, eat_monitor);
		x_lock_mutex(mutex_fork, eat_monitor);
	}
	else
	{
		x_lock_mutex(mutex_fork, eat_monitor);
		x_lock_mutex(mutex_next_fork, eat_monitor);
	}
}

static void	unlock_mutex_forks(t_pthread_node *node_th, \
		t_fork_node *node_fork, t_eat_monitor *eat_monitor)
{
	pthread_mutex_t		*mutex_fork;
	pthread_mutex_t		*mutex_next_fork;

	mutex_fork = &node_fork->mutex_fork;
	mutex_next_fork = &node_fork->next->mutex_fork;
	if (case_tail_person(node_th))
	{
		x_unlock_mutex(mutex_next_fork, eat_monitor);
		x_unlock_mutex(mutex_fork, eat_monitor);
	}
	else
	{
		x_unlock_mutex(mutex_fork, eat_monitor);
		x_unlock_mutex(mutex_next_fork, eat_monitor);
	}
}

// x_lock_mutexのerrの格納先 phへ？
int	run_eating(t_pthread_node *node_th, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	t_eat_monitor		*eat_monitor;

	eat_monitor = &node_th->ph->eat_monitor;
	lock_mutex_forks(node_th, node_fork, eat_monitor);
	put_state(TAKEN_FORK, node_th, 0, id);
	put_state(EATING, node_th, time_eat, id);
	node_th->flag_wait_cnt = true;
	unlock_mutex_forks(node_th, node_fork, eat_monitor);
	return (SUCCESS);
}
