/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:53:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	strdup_status_array(t_ph *ph);
static bool	make_list(t_ph *ph);

bool	build_struct_and_list(t_ph *ph, int argc)
{
	if (argc == 6)
		ph->flag_must_eat = true;
	if (!strdup_status_array(ph))
		return (false);
	if (!make_list(ph))
		return (false);
	ph->sleep_time = ph->argv[4];
	ph->ate_all_monitor.ph = ph;
	ph->ate_all_monitor.num_people = ph->argv[1];
	ph->ate_all_monitor.flag_must_eat = ph->flag_must_eat;
	ph->ate_all_monitor.mtx_st = &ph->mtx_st;
	ph->err_monitor.ph = ph;
	ph->err_monitor.num_people = ph->argv[1];
	ph->err_monitor.mtx_st = &ph->mtx_st;
	ph->die_monitor.ph = ph;
	ph->die_monitor.num_people = ph->argv[1];
	ph->die_monitor.mtx_st = &ph->mtx_st;
	ph->hungry_monitor.ph = ph;
	ph->hungry_monitor.num_people = ph->argv[1];
	ph->hungry_monitor.mtx_st = &ph->mtx_st;
	return (true);
}

static bool	strdup_status_array(t_ph *ph)
{
	size_t	i;

	ph->status[0] = x_strdup(&ph->alloc_list, TAKEN_FORK_STR);
	ph->status[1] = x_strdup(&ph->alloc_list, EATING_STR);
	ph->status[2] = x_strdup(&ph->alloc_list, SLEEPING_STR);
	ph->status[3] = x_strdup(&ph->alloc_list, THINKING_STR);
	ph->status[4] = x_strdup(&ph->alloc_list, DIED_STR);
	i = 0;
	while (i < NUM_OF_TYPES)
	{
		if (ph->status[i] == NULL)
		{
			set_err_num_ph(ph, ERR_STRDUP);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	make_list(t_ph *ph)
{
	size_t	id;

	id = 0;
	while (id < ph->argv[1])
	{
		if (!add_philo_list(ph, &ph->philo_list, &ph->alloc_list, id))
			return (false);
		if (!add_fork_list(ph, &ph->fork_list, &ph->alloc_list, id))
			return (false);
		id++;
	}
	return (true);
}
