/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_monitor_ate_all.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 13:26:17 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	judge_ate_all(t_ph *ph, size_t num_people);

void	*run_monitor_ate_all(void *ptr)
{
	t_monitor	*monitor;
	t_ph		*ph;
	size_t		num_people;

	monitor = (t_monitor *)ptr;
	ph = monitor->ph;
	num_people = monitor->num_people;
	while (!is_end(&ph->end_st, &ph->mtx_st))
	{
		if (monitor->flag_must_eat == true)
		{
			if (judge_ate_all(ph, num_people))
				break ;
		}
	}
	return (ptr);
}

static bool	judge_ate_all(t_ph *ph, size_t num_people)
{
	t_mutex	*mtx_st;

	mtx_st = &ph->mtx_st;
	x_lock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
	if (ph->ate_st.ate_cnt >= num_people && ph->ate_st.ate_all == false)
	{
		x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
		if (!x_usleep_millisec(ph, ph->argv[3]))
			return (false);
		x_lock_mutex_struct(&mtx_st->mtx_ate_all, &ph->mtx_st);
		ph->ate_st.ate_all = true;
		x_unlock_mutex_struct(&mtx_st->mtx_ate_all, &ph->mtx_st);
		x_lock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
		ph->end_st.flag_end = true;
		x_unlock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
		return (true);
	}
	x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
	return (false);
}
