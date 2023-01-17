/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 02:17:19 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);

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

bool	is_hungly(t_philo_node *node_philo)
{
	t_philo_node	*node_next_philo;
	t_philo_node	*node_prev_philo;

	x_lock_mutex_philo(node_philo);
	node_next_philo = node_philo->next;
	node_prev_philo = node_philo->prev;
	x_unlock_mutex_philo(node_philo);
	x_lock_mutex_philo(node_next_philo);
	if (node_next_philo->hungry == true)
	{
		x_unlock_mutex_philo(node_next_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_next_philo);
	x_lock_mutex_philo(node_prev_philo);
	if (node_prev_philo->hungry == true)
	{
		x_unlock_mutex_philo(node_prev_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_prev_philo);
	return (false);
}

static void	run_case_normal(t_philo_main *ph, \
			t_philo_node *node_philo, t_fork_node *node_fork)
{
	while (1)
	{
		if (is_end(&ph->end_struct, &ph->mutex_struct))
			return ;
		if (is_hungly(node_philo))
			continue ;
		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			return ;
		if (!put_state(SLEEPING, node_philo, ph->argv[4], node_philo->id))
			return ;
		if (!put_state(THINKING, node_philo, 0, node_philo->id))
			return ;
	}
	return ;
}


	// if (node_philo->id % 2 == 1)
	// {
	// 	if (!x_usleep(ph, 100))
	// 		return ;
	// }
	
// static void	*put_sleep_think(void *ptr)
// {
// 	t_philo_node	*node_philo;
// 	long			time_sleep;

// 	node_philo = (t_philo_node *)ptr;
// 	time_sleep = node_philo->ph->argv[4];
// 	if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
// 		return (NULL);
// 	// if (!put_state(THINKING, node_philo, 0, node_philo->id))
// 	// 	return (NULL);
// 	return (ptr);
// }

// static void	*put_eat(void *ptr)
// {
// 	t_philo_node	*node_philo;

// 	node_philo = (t_philo_node *)ptr;
// 	if (!run_eating(node_philo, node_philo->node_fork, node_philo->id, node_philo->ph->argv[3]))
// 		return (NULL);
// 	return (ptr);
// }

// // usleep
// static void	run_case_normal(t_philo_main *ph, \
// 			t_philo_node *node_philo, t_fork_node *node_fork)
// {
// 	(void)node_fork;
// 	if (node_philo->id % 2 == 1)
// 	{
// 		if (!x_usleep(ph, 100))
// 			return ;
// 	}
// 	while (1)
// 	{
// 		if (!x_pthread_create(ph, &node_philo->philo_eat_th, \
// 						put_eat, node_philo))
// 			return ;
// 		if (pthread_join(node_philo->philo_eat_th, NULL) != 0)
// 		{
// 			get_err_num_ph(ph, ERR_PTHREAD_JOIN);
// 			return ;
// 		}

// 		// if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
// 		// 	return ;
			
// 		// if (!x_pthread_create(ph, &node_philo->philo_sleep_th, \
// 		// 				put_sleep_think, node_philo))
// 		// 	return ;
// 		// if (pthread_join(node_philo->philo_sleep_th, NULL) != 0)
// 		// {
// 		// 	get_err_num_ph(ph, ERR_PTHREAD_JOIN);
// 		// 	return ;
// 		// }

// 		if (!put_state(SLEEPING, node_philo, ph->argv[4], node_philo->id))
// 			return ;
// 		if (!put_state(THINKING, node_philo, 0, node_philo->id))
// 			return ;
// 	}
// 	return ;
// }
