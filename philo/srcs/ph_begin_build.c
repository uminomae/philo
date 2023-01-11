/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 19:23:47 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	make_list(t_philo_main *ph)
{
	size_t	id;

	id = 0;
	while (id < ph->argv[1])
	{
		if (add_pthread_list(ph, &ph->thread_list, &ph->alloc_list, id) == 1)
			get_err_num_ph(ph, ERR_ADD_PTHREAD_LIST);
		if (add_fork_list(&ph->fork_list, &ph->alloc_list, id) == 1)
			get_err_num_ph(ph, ERR_ADD_FORK_LIST);
		if (add_pthread_list(ph, &ph->thread_list, &ph->alloc_list, id) == 1)
			get_err_num_ph(ph, ERR_ADD_MONITOR_LIST);
		id++;
	}
}

static void	strdup_status_array(t_philo_main *ph)
{
	ph->status[0] = x_strdup(&ph->alloc_list, TAKEN_FORK_STR);
	ph->status[1] = x_strdup(&ph->alloc_list, EATING_STR);
	ph->status[2] = x_strdup(&ph->alloc_list, SLEEPING_STR);
	ph->status[3] = x_strdup(&ph->alloc_list, THINKING_STR);
	ph->status[4] = x_strdup(&ph->alloc_list, DIED_STR);
}

int	build_struct_and_list(t_philo_main *ph, int argc)
{
	if (argc == 6)
		ph->flag_must_eat = true;
	strdup_status_array(ph);
	make_list(ph);
	ph->sleep_seconds = ph->argv[4];
	ph->end_monitor.ph = ph;
	if (ph->flag_err == true)
	{
		printf("%s", ERR_STR);
		return (1);
	}
	return (0);
}
