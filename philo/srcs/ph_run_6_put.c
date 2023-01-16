/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_6_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 02:08:44 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	wait_action_usleep_ms(t_philo_main *ph, \
				long start, size_t wait_ms);

bool	put_state(size_t num_state, t_philo_node *node_philo, \
				long ms, size_t id)
{
	long				time_current;
	const t_philo_main	*ph = node_philo->ph;

	if (!gettimeofday_millisec(node_philo->ph, &time_current))
		return (false);
	x_lock_mutex_philo(node_philo);
	node_philo->time[num_state] = time_current;
	x_unlock_mutex_philo(node_philo);
	if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		return (false);
	if (put_stamp(node_philo->time[num_state], id, ph->status[num_state]) < 0)
		get_err_num_philo(node_philo, ERR_PRINTF);
	if (ms > 0)
	{
		if (!wait_action_usleep_ms(node_philo->ph, \
							node_philo->time[num_state], ms))
			return (false);
	}
	if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		return (false);
	return (true);
}

int	put_stamp(long time, size_t id, const char *state)
{
	int	ret;

	ret = printf("%ld %zu %s\n", time, id, state);
	return (ret);
}

static bool	wait_action_usleep_ms(t_philo_main *ph, long start, size_t wait_ms)
{
	long	total;
	long	current;

	total = wait_ms + start;
	if (!gettimeofday_millisec(ph, &current))
		return (false);
	while (total > current)
	{
		if (total - current > 5)
		{
			if (!x_usleep_millisec(ph, (total - current) / 2))
				return (false);
		}
		if (!gettimeofday_millisec(ph, &current))
			return (false);
	}
	return (true);
}
