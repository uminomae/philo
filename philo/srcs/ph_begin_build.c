/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 13:27:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	strdup_status_array(t_philo_main *ph);
static bool	make_list(t_philo_main *ph);

bool	build_struct_and_list(t_philo_main *ph, int argc)
{
	if (argc == 6)
		ph->flag_must_eat = true;
	if (!strdup_status_array(ph))
		return (false);
	if (!make_list(ph))
		return (false);
	ph->monitor_node.ph = ph;
	ph->monitor_node.num_people = ph->argv[1];
	ph->sleep_seconds = ph->argv[4];
	// if (ph->error_num > NUM_ERR_LOW)
	// 	return (false);
	// printf("---------a\n");
	return (true);
}

static bool	strdup_status_array(t_philo_main *ph)
{
	size_t	i;
	
	ph->status[0] = x_strdup(&ph->alloc_list, TAKEN_FORK_STR);
	ph->status[1] = x_strdup(&ph->alloc_list, EATING_STR);
	ph->status[2] = x_strdup(&ph->alloc_list, SLEEPING_STR);
	ph->status[3] = x_strdup(&ph->alloc_list, THINKING_STR);
	ph->status[4] = x_strdup(&ph->alloc_list, DIED_STR);
	// ph->status[4] = NULL;
	i = 0;
	while (i < NUM_OF_TYPES)
	{
		if (ph->status[i] == NULL)
		{
			get_err_num_ph(ph, ERR_STRDUP);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	make_list(t_philo_main *ph)
{
	size_t	id;

	id = 0;
	while (id < ph->argv[1])
	{
		// if (add_philo_list(ph, &ph->philo_list, &ph->alloc_list, id))
		if (!add_philo_list(ph, &ph->philo_list, &ph->alloc_list, id))
		{
			get_err_num_ph(ph, ERR_ADD_PHILO_LIST);
			return (false);
		}
		// if (add_fork_list(ph, &ph->fork_list, &ph->alloc_list, id))
		if (!add_fork_list(ph, &ph->fork_list, &ph->alloc_list, id))
		{
			get_err_num_ph(ph, ERR_ADD_FORK_LIST);
			return (false);
		}
		id++;
	}
	return (true);

}
