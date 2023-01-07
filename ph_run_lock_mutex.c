/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 01:14:08 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_mutex(pthread_mutex_t *mutex, t_monitor *monitor)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret != 0)
		get_err_flag_monitor(monitor);
}

static void	unlock_mutex(pthread_mutex_t *mutex, t_monitor *monitor)
{
	int	ret;

	ret = pthread_mutex_unlock(mutex);
	if (ret != 0)
		get_err_flag_monitor(monitor);
}

static void	toggle_mutex(size_t flag, t_monitor *monitor, t_fork_node *node_fork)
{

	if (flag == LOCK)
	{
		lock_mutex(&node_fork->mutex, monitor);
		lock_mutex(&node_fork->next->mutex, monitor);
		lock_mutex(&monitor->mutex, monitor);
	}
	else if (flag == UNLOCK)
	{
		unlock_mutex(&monitor->mutex, monitor);
		unlock_mutex(&node_fork->next->mutex, monitor);
		unlock_mutex(&node_fork->mutex, monitor);
	}
}

static bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == TRUE && node_th->times_must_eat == cnt)
		return (TRUE);
	return (false);
}

int	lock_mutex_and_eat_starting(t_pthread_node *node_th, t_fork_node *node_fork, size_t id)
{
	toggle_mutex(LOCK, &node_th->ph->monitor, node_fork);
	if (node_th->ph->monitor.ate_all == TRUE)
	{
		toggle_mutex(UNLOCK, &node_th->ph->monitor, node_fork);
		return (1);
	}
	change_state_and_putstamp(TAKEN_FORK, node_th, 0, id);
	change_state_and_putstamp(EATING, node_th, node_th->ph->argv[3], id);
	node_th->cnt++;
	if (is_required_times_ate(node_th, node_th->cnt))
		node_th->ph->monitor.ate_cnt++;
	if (node_th->ph->monitor.ate_cnt == node_th->ph->argv[1])
	{
		node_th->ph->monitor.ate_all = TRUE;
		toggle_mutex(UNLOCK, &node_th->ph->monitor, node_fork);
		return (1);
	}
	toggle_mutex(UNLOCK, &node_th->ph->monitor, node_fork);
	return (0);
}