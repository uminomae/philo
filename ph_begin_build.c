/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 15:37:30 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO err
static void	argv_to_int(t_philo *ph, int argc, char **argv)
{
	int	i;
	int	ret;

	i = 0;
	while (i < argc)
	{
		ret = ph_atoi(argv[i]);
		if (ret == -1)
			process_error(ph);
		ph->argv[i] = (size_t)ret;
		i++;
	}
}

static void	make_fork_list(t_philo *ph)
{
	size_t	id_fork;

	id_fork = 0;
	while (id_fork < ph->argv[1])
	{
		add_list(&ph->fork_list, &ph->alloc_list, id_fork);
		id_fork++;
	}
}

static void	make_pthread_list(t_philo *ph)
{
	size_t	id;	

	id = 0;
	while (id < ph->argv[1])
	{
		add_pthread_list(ph, &ph->thread_list, &ph->alloc_list, id);
		id++;
	}
}

static void	init_status_array(t_philo *ph)
{
	//TODO free
	ph->status[0] = x_strdup(&ph->alloc_list, TAKEN_FORK_STR);
	ph->status[1] = x_strdup(&ph->alloc_list, EATING_STR);
	ph->status[2] = x_strdup(&ph->alloc_list, SLEEPING_STR);
	ph->status[3] = x_strdup(&ph->alloc_list, THINKING_STR);
	ph->status[4] = x_strdup(&ph->alloc_list, DIED_STR);
}

void	build_struct_and_list(t_philo *ph, int argc, char **argv)
{
	if (argc == 6)
		ph->must_eat = TRUE;
	argv_to_int(ph, argc, argv);
	init_status_array(ph);
	ph->sleep_seconds = ph->argv[4];
	make_fork_list(ph);
	make_pthread_list(ph);
}
