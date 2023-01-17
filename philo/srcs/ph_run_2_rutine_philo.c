/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 21:41:37 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
// static void	*put_sleep_think(void *ptr);

void	*run_rutine_philo(void *ptr)
{
	t_philo_node	*node_philo;
	t_fork_node		*node_fork;

	node_philo = (t_philo_node *)ptr;
	node_fork = get_fork_node(&node_philo->ph->fork_list, node_philo->id);
	node_philo->node_fork = node_fork;
	if (node_philo->ph->argv[1] == 1)
		run_case_1person(node_philo, node_fork);
	else
		run_case_normal(node_philo->ph, node_philo, node_fork);
	return (ptr);
}

// static void	*put_eat(void *ptr)
// {
// 	t_philo_node	*node_philo;
// 	long			time_eat;

// 	node_philo = (t_philo_node *)ptr;
// 	time_eat = node_philo->ph->argv[3];
// 	if (!run_eating(node_philo, node_philo->node_fork, node_philo->id, time_eat))
// 		return (NULL);
// 	return (ptr);
// }

// usleep
static void	run_case_normal(t_philo_main *ph, \
			t_philo_node *node_philo, t_fork_node *node_fork)
{
	(void)node_fork;
	if (node_philo->id % 2 == 1)
	{
		if (!x_usleep(ph, 100))
			return ;
	}
	while (1)
	{
		// if (!x_pthread_create(ph, &node_philo->philo_eat_th, \
		// 				put_eat, node_philo))
		// 	return ;
		// if (pthread_join(node_philo->philo_eat_th, NULL) != 0)
		// {
		// 	get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		// 	return ;
		// }

		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			return ;
			
		// if (!x_pthread_create(ph, &node_philo->philo_sleep_th, \
		// 				put_sleep_think, node_philo))
		// 	return ;
		// if (pthread_join(node_philo->philo_sleep_th, NULL) != 0)
		// {
		// 	get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		// 	return ;
		// }

		if (!put_state(SLEEPING, node_philo, ph->argv[4], node_philo->id))
			return ;
		if (!put_state(THINKING, node_philo, 0, node_philo->id))
			return ;
	}
	return ;
}


