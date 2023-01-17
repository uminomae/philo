/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 20:23:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
// static bool	is_awake(t_philo_node *node_philo);
static void	count_ate_in_philo(t_philo_node *node_philo);
// static void	*put_sleep_think(void *ptr);

void	*run_rutine_philo(void *ptr)
{
	t_philo_node	*node_philo;
	t_fork_node		*node_fork;

	node_philo = (t_philo_node *)ptr;
	node_fork = get_fork_node(&node_philo->ph->fork_list, node_philo->id);
	if (node_philo->ph->argv[1] == 1)
		run_case_1person(node_philo, node_fork);
	else
		run_case_normal(node_philo->ph, node_philo, node_fork);
	return (ptr);
}

// usleep
static void	run_case_normal(t_philo_main *ph, \
			t_philo_node *node_philo, t_fork_node *node_fork)
{
	if (node_philo->id % 2 == 1)
	{
		if (!x_usleep(ph, 100))
			return ;
	}
	while (1)
	{
		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			return ;
		if (ph->flag_must_eat == true)
			count_ate_in_philo(node_philo);
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

static void	count_ate_in_philo(t_philo_node *node_philo)
{
	t_mutex	*mutex_struct;

	mutex_struct = &node_philo->ph->mutex_struct;
	x_lock_mutex_philo(node_philo);
	if (node_philo->times_must_eat == node_philo->cnt)
	{
		x_unlock_mutex_philo(node_philo);
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
	x_unlock_mutex_philo(node_philo);
}

// static void	*put_sleep_think(void *ptr)
// {
// 	t_philo_node	*node_philo;
// 	long			time_sleep;

// 	node_philo = (t_philo_node *)ptr;
// 	time_sleep = node_philo->ph->argv[4];
// 	if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
// 		return (NULL);
// 	if (!put_state(THINKING, node_philo, 0, node_philo->id))
// 		return (NULL);
// 	return (ptr);
// }
