/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_eating.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 04:53:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == true && node_th->times_must_eat == cnt)
		return (true);
	return (false);
}

bool	is_ate_all(t_eat_monitor *eat_monitor)
{
	if (eat_monitor->ate_all == true)
	{
		x_unlock_mutex(&eat_monitor->mutex_eat, eat_monitor);
		return (true);
	}
	return (false);
}

bool	judge_ate_all(t_eat_monitor *eat_monitor, size_t num_people)
{
	if (eat_monitor->ate_cnt == num_people)
	{
		eat_monitor->ate_all = true;
		x_unlock_mutex(&eat_monitor->mutex_eat, eat_monitor);
		return (true);
	}
	return (false);
}

void	count_ate_person(t_pthread_node *node_th)
{
	long	time_current;
	long	time_ate;

	time_current = get_time_milli_sec() - node_th->start_time;
	if (time_current < 0)
		node_th->flag_err = true;
	time_ate = node_th->time[EATING] + node_th->ph->argv[3];
	if (time_current > time_ate)
	{
		if(node_th->flag_wait_cnt == true)
		{
			node_th->cnt++;
			node_th->flag_wait_cnt = false;
		}
	}
}

int	run_eating(t_pthread_node *node_th, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	// pthread_mutex_t		*mutex_fork;
	// t_eat_monitor		*eat_monitor;
	x_lock_mutex(&node_fork->mutex_fork, &node_th->ph->eat_monitor);
	x_lock_mutex(&node_fork->next->mutex_fork, &node_th->ph->eat_monitor);
	change_state_and_putstamp(TAKEN_FORK, node_th, 0, id);
	change_state_and_putstamp(EATING, node_th, time_eat, id);
	node_th->flag_wait_cnt = true;;
	x_unlock_mutex(&node_fork->next->mutex_fork, &node_th->ph->eat_monitor);
	x_unlock_mutex(&node_fork->mutex_fork, &node_th->ph->eat_monitor);
	return (SUCCESS);
}