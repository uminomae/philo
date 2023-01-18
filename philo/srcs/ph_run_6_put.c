/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_6_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/19 01:59:51 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	wait_action_usleep_ms(t_philo_main *ph, \
				long start, size_t wait_ms);

bool	put_state(size_t state, t_philo_node *node_philo, \
				long ms, size_t id)
{
	long	elapsed_time;

	if (!get_time_from_start(node_philo->ph, &elapsed_time))
		return (false);
	if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		return (false);
	x_lock_mutex_philo(node_philo);
	node_philo->time[state] = elapsed_time;
	if (put_stamp(node_philo->time[state], id, \
					node_philo->ph->status[state]) == -1)
	{
		x_unlock_mutex_philo(node_philo);
		get_err_num_philo(node_philo, ERR_PRINTF);
		return (false);
	}
	x_unlock_mutex_philo(node_philo);
	if (ms > 0)
	{
		if (!wait_action_usleep_ms(node_philo->ph, node_philo->time[state], ms))
		{
			return (false);
		}
	}
	if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		return (false);
	return (true);
}

int	put_stamp(long time, size_t id, char *state)
{
	int	ret;

	ret = printf("%ld %zu %s\n", time, id, state);
	// ret = -1;
	return (ret);
}

static bool	wait_action_usleep_ms(t_philo_main *ph, long start, size_t wait_ms)
{
	long	total;
	long	elapsed_time;

	total = wait_ms + start;
	if (!get_time_from_start(ph, &elapsed_time))
		return (false);
	while (total > elapsed_time)
	{
		if (total - elapsed_time > 5)
		{
			if (!x_usleep_millisec(ph, (total - elapsed_time) / 2))
				return (false);
		}
		if (!get_time_from_start(ph, &elapsed_time))
			return (false);
	}
	return (true);
}
