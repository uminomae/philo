/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_lock_mutex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 03:28:38 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == true && node_th->times_must_eat == cnt)
		return (true);
	return (false);
}

bool	is_ate_all(t_monitor *monitor)
{
	if (monitor->ate_all == true)
	{
		x_pthread_mutex_unlock(&monitor->mutex, monitor);
		return (true);
	}
	return (false);
}

bool	check_ate_all(t_monitor *monitor, size_t num_people)
{
	if (monitor->ate_cnt == num_people)
	{
		monitor->ate_all = true;
		x_pthread_mutex_unlock(&monitor->mutex, monitor);
		return (true);
	}
	return (false);
}


// TODO gettime err
void	count_times_end_eating(t_pthread_node *node_th)
{
	long	time_current;
	long	time_ate;

	time_current = get_time_milli_sec() - node_th->start_time;
	time_ate = node_th->time[EATING] + node_th->ph->argv[3];
	if (time_current > time_ate)
		node_th->cnt++;
}

// 食べ終えてからdied判定する
//TODO longへ?argv
int	run_eating(t_pthread_node *node_th, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	x_pthread_mutex_lock(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	if (is_ate_all(&node_th->ph->monitor))
		return (ATE_ALL);
	x_pthread_mutex_unlock(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	x_pthread_mutex_lock(&node_fork->mutex, &node_th->ph->monitor);
	x_pthread_mutex_lock(&node_fork->next->mutex, &node_th->ph->monitor);
	change_state_and_putstamp(TAKEN_FORK, node_th, 0, id);
	change_state_and_putstamp(EATING, node_th, time_eat, id);
	// node_th->cnt++;
	x_pthread_mutex_unlock(&node_fork->next->mutex, &node_th->ph->monitor);
	x_pthread_mutex_unlock(&node_fork->mutex, &node_th->ph->monitor);
	x_pthread_mutex_lock(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	if (is_required_times_ate(node_th, node_th->cnt))
		node_th->ph->monitor.ate_cnt++;
	if (check_ate_all(&node_th->ph->monitor, node_th->ph->argv[1]))
		return (ATE_ALL);
	x_pthread_mutex_unlock(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	return (SUCCESS);
}
