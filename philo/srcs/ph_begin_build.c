/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 20:04:11 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	make_fork_list(t_philo *ph)
{
	size_t	id_fork;
	size_t	ret;

	id_fork = 0;
	while (id_fork < ph->argv[1])
	{
		ret = add_fork_list(&ph->fork_list, &ph->alloc_list, id_fork);
		if (ret == 1)
		{
			get_err_flag(ph);
			return ;
		}
		id_fork++;
	}
}

static void	make_pthread_list(t_philo *ph)
{
	size_t	id;
	size_t	ret;

	id = 0;
	while (id < ph->argv[1])
	{
		ret = add_pthread_list(ph, &ph->thread_list, &ph->alloc_list, id);
		if (ret == 1)
		{
			get_err_flag(ph);
			return ;
		}
		id++;
	}
}

static void	strdup_status_array(t_philo *ph)
{
	ph->status[0] = x_strdup(&ph->alloc_list, TAKEN_FORK_STR);
	ph->status[1] = x_strdup(&ph->alloc_list, EATING_STR);
	ph->status[2] = x_strdup(&ph->alloc_list, SLEEPING_STR);
	ph->status[3] = x_strdup(&ph->alloc_list, THINKING_STR);
	ph->status[4] = x_strdup(&ph->alloc_list, DIED_STR);
}

int	build_struct_and_list(t_philo *ph, int argc)
{
	if (argc == 6)
		ph->flag_must_eat = true;
	strdup_status_array(ph);
	ph->sleep_seconds = ph->argv[4];
	make_fork_list(ph);
	make_pthread_list(ph);
	ph->eat_monitor.ph = ph;
	if (ph->flag_err == true)
	{
		printf("%s", ERR_STR);
		return (1);
	}
	return (0);
}
