/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_rutine_err_monitor.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:38:13 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_monitor_error(void *ptr)
{
	t_monitor	*err_monitor;
	t_ph		*ph;
	long		elapsed_time;
	long		prev;

	err_monitor = (t_monitor *)ptr;
	ph = err_monitor->ph;
	prev = ph->start_time;
	while (!is_end(&ph->end_st, &ph->mtx_st))
	{
		if (!get_time_from_start(ph, &elapsed_time))
			return (false);
		if (prev + WAIT_REGULARLY < elapsed_time)
		{
			prev = elapsed_time;
			if (is_error(ph))
				set_flag_end(ph, &ph->mtx_st.mtx_end, &ph->mtx_st);
		}
	}
	return (ptr);
}

bool	is_error(t_ph *ph)
{
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	if (ph->mtx_st.err_num > NUM_ERR_LOW)
		ph->err_num = ph->mtx_st.err_num;
	if (ph->err_num > NUM_ERR_LOW)
	{
		x_unlock_mutex_ph(&ph->mutex_ph, ph);
		return (true);
	}
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	return (false);
}
