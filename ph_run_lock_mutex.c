/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_lock_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 13:09:15 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	toggle_mutex(size_t flag, t_monitor *monitor, t_fork_node *node_fork)
{

	if (flag == LOCK)
	{
		x_pthread_mutex_lock(&node_fork->mutex, monitor);
		x_pthread_mutex_lock(&node_fork->next->mutex, monitor);
		x_pthread_mutex_lock(&monitor->mutex, monitor);
	}
	else if (flag == UNLOCK)
	{
		x_pthread_mutex_unlock(&monitor->mutex, monitor);
		x_pthread_mutex_unlock(&node_fork->next->mutex, monitor);
		x_pthread_mutex_unlock(&node_fork->mutex, monitor);
	}
}

bool	is_ate_all(t_monitor *monitor, t_fork_node *node_fork)
{
	if (monitor->ate_all == true)
	{
		toggle_mutex(UNLOCK, monitor, node_fork);
		return (true);
	}
	return (false);

}

static bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == TRUE && node_th->times_must_eat == cnt)
		return (TRUE);
	return (false);
}

bool	check_ate_all(t_monitor *monitor, t_fork_node *node_fork, size_t num_people)
{
	if (monitor->ate_cnt == num_people)
	{
		monitor->ate_all = true;
		toggle_mutex(UNLOCK, monitor, node_fork);
		return (true);
	}
	return (false);
}

//TODO longへ?argv
int	run_eating(t_pthread_node *node_th, t_fork_node *node_fork, size_t id, long time_eat)
{
	toggle_mutex(LOCK, &node_th->ph->monitor, node_fork);
	if (is_ate_all(&node_th->ph->monitor, node_fork))
		return (ATE_ALL);
	change_state_and_putstamp(TAKEN_FORK, node_th, 0, id);
	change_state_and_putstamp(EATING, node_th, time_eat, id);
	node_th->cnt++;
	if (is_required_times_ate(node_th, node_th->cnt))
		node_th->ph->monitor.ate_cnt++;
	if (check_ate_all(&node_th->ph->monitor, node_fork, node_th->ph->argv[1]))
		return (ATE_ALL);
	toggle_mutex(UNLOCK, &node_th->ph->monitor, node_fork);
	return (SUCCESS);
}