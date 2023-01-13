/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_dining_philo_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 11:34:12 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	run_case_1person(t_philo_node	*node_th)
{
	while (1)
	{
		if (check_time_to_die(node_th, get_time_milli_sec()))
			return (1);
	}
}

void	run_rutine_philo(t_philo_node	*node_philo, t_fork_node *node_fork)
{
	const long time_eat = node_philo->ph->argv[3];
	while (1)
	{
		// printf("run philo a\n");
		// judge end flag 
		x_lock_mutex_philo(node_philo);
		if (node_philo->flag_end == true)
		{
			x_unlock_mutex_philo(node_philo);
			break ;
		}
		x_unlock_mutex_philo(node_philo);

		// count_ate_person(node_philo);
		
		// if (check_time_to_die(node_philo, get_time_milli_sec()))
		// 	break ;
		count_ate_in_philo(node_philo);

			// printf("c\n");

		// x_lock_mutex_philo(node_philo);
		// printf("run philo b\n");
		run_eating(node_philo, node_fork, node_philo->id, \
			time_eat);
				printf("------ cnt philo %zu id:%zu\n", node_philo->cnt, node_philo->id);

		// run_eating(node_philo, node_fork, node_philo->id, \
		// 	node_philo->ph->argv[3]);
		// x_unlock_mutex_philo(node_philo);

		printf("run philo c\n");
		put_state(SLEEPING, node_philo, \
				node_philo->ph->argv[4], node_philo->id);
		put_state(THINKING, node_philo, 0, node_philo->id);
	}
}

void	*run_rutine_dining_philo_in_thread(void *ptr)
{
	t_philo_node	*node_th;
	t_fork_node		*node_fork;

	node_th = (t_philo_node *)ptr;
	node_fork = get_fork_node(&node_th->ph->fork_list, node_th->id);
	if (node_th->ph->argv[1] == 1)
		run_case_1person(node_th);
	else
		run_rutine_philo(node_th, node_fork);
	return (NULL);
}
