/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:49:48 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_rutine_monitor(void *ptr)
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
		if (judge_time_to_die(ph, num_people))
			break ;
		if (!judge_hungry(ph, num_people))
			set_flag_end(ph, &ph->mtx_st.mtx_end, &ph->mtx_st);
	}
	return (ptr);
}
