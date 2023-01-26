/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 12:12:17 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	wait_action_usleep_ms(t_ph *ph, \
				long start, size_t wait_ms);

bool	put_state(size_t state, t_philo *node_ph, long ms, size_t id)
{
	long	elapsed_time;

	x_lock_mutex_philo(node_ph, &node_ph->mutex_put);
	if (is_end(&node_ph->ph->end_st, &node_ph->ph->mtx_st))
	{
		x_unlock_mutex_philo(node_ph, &node_ph->mutex_put);
		return (false);
	}
	x_lock_mutex_philo(node_ph, &node_ph->mutex_philo);
	if (!get_time_from_start(node_ph->ph, &elapsed_time))
		x_unlock_mutex_philo(node_ph, &node_ph->mutex_put);
	node_ph->time[state] = elapsed_time;
	if (put_stamp(node_ph->time[state], id, node_ph->ph->status[state]) == -1)
		set_err_num_philo(node_ph, ERR_PRINTF);
	x_unlock_mutex_philo(node_ph, &node_ph->mutex_philo);
	x_unlock_mutex_philo(node_ph, &node_ph->mutex_put);
	if (node_ph->err_num > NUM_ERR_LOW || node_ph->ph->err_num > NUM_ERR_LOW)
		return (false);
	if (ms > 0)
	{
		if (!wait_action_usleep_ms(node_ph->ph, node_ph->time[state], ms))
			return (false);
	}
	return (true);
}

int	put_stamp(long time, size_t id, char *state)
{
	int	ret;

	ret = printf("%ld %zu %s\n", time, id, state);
	return (ret);
}

static bool	wait_action_usleep_ms(t_ph *ph, long start, size_t wait_ms)
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

bool	put_died(t_ph *ph)
{
	long	elapsed_time;
	t_mutex	*mtx_st;

	mtx_st = &ph->mtx_st;
	x_lock_mutex_struct(&mtx_st->mtx_die, mtx_st);
	if (ph->ate_st.ate_cnt == true)
	{
		x_unlock_mutex_struct(&mtx_st->mtx_die, mtx_st);
		return (true);
	}
	if (ph->died_st.died_flag)
	{
		if (!get_time_from_start(ph, &elapsed_time))
		{
			x_unlock_mutex_struct(&mtx_st->mtx_die, mtx_st);
			return (false);
		}
		if (!put_stamp(elapsed_time, ph->died_st.died_id, DIED_STR))
		{
			x_unlock_mutex_struct(&mtx_st->mtx_die, mtx_st);
			return (false);
		}
	}
	x_unlock_mutex_struct(&mtx_st->mtx_die, mtx_st);
	return (true);
}
