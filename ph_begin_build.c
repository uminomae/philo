/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/04 00:48:35 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	convert_argv_to_int(t_philo *ph, int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		ph->argv[i] = (size_t)ph_atoi(argv[i]);
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
	size_t	id_th;	

	id_th = 0;
	while (id_th < ph->argv[1])
	{
		add_pthread_list(&ph->thread_list, &ph->alloc_list, id_th);
		id_th++;
	}
}

static void	make_function_ptr_array(t_philo *ph)
{
	ph->put_type[TAKEN_FORK] = put_taken_fork;
	ph->put_type[EATING] = put_eating;
	ph->put_type[SLEEPING] = put_sleeping;
	ph->put_type[THINKING] = put_thinking;
	ph->put_type[DIED] = put_died;
}

void	build_struct_and_list(t_philo *ph, int argc, char **argv)
{
	convert_argv_to_int(ph, argc, argv);
	ph->sleep_seconds = ph->argv[4];
	make_fork_list(ph);
	make_pthread_list(ph);
	make_function_ptr_array(ph);
}
