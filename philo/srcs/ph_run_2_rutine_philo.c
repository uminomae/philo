/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 11:18:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// /philo 4 310 200 100
// 1673917590367 0 has taken a fork
// 1673917590367 0 has taken a fork
// 1673917590367 0 is eating
// 1673917590367 2 has taken a fork
// 1673917590367 2 has taken a fork
// 1673917590367 2 is eating
// 1673917590567 3 has taken a fork
// 1673917590567 3 has taken a fork
// 1673917590567 3 is eating
// 1673917590567 2 has taken a fork
// 1673917590567 1 has taken a fork
// 1673917590567 0 is sleeping
// 1673917590567 2 is sleeping
// 1673917590667 2 is thinking
// 1673917590667 0 is thinking

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
// static bool	is_awake(t_philo_node *node_philo);
static void	count_ate_in_philo(t_philo_node *node_philo);
static void	*put_sleep_think(void *ptr);

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

static void	run_case_normal(t_philo_main *ph, \
			t_philo_node *node_philo, t_fork_node *node_fork)
{
	// const long	sleep_time = node_philo->time[EATING] + node_philo->ph->argv[4];
	// long		current;

	if (node_philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		// printf("---- normal 1\n");
		// while (!is_awake(node_philo))
		// {
		// 	if (is_end(&ph->end_struct, &ph->mutex_struct))
		// 		return ;
		// 	if (!gettimeofday_millisec(node_philo->ph, &current))
		// 		return ;
		// 	wait_required_time(node_philo->ph, sleep_time, current);
		// }
		// printf("---- normal 2\n");
		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			return ;
		if (ph->flag_must_eat == true)
			count_ate_in_philo(node_philo);
		// printf("---- normal 3\n");
		x_pthread_create(ph, &node_philo->philo_sleep_th, \
						put_sleep_think, node_philo);
		// if (!x_pthread_detach(ph, &node_philo->philo_sleep_th))
		// 	return ;
		// printf("---- normal 4\n");
		if (pthread_join(node_philo->philo_sleep_th, NULL) != 0)
			get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		// printf("---- normal 5\n");
	}
	return ;
}

// static bool	is_awake(t_philo_node *node_philo)
// {
// 	x_lock_mutex_philo(node_philo);
// 	if (node_philo->flag_sleeping == false)
// 	{
// 		x_unlock_mutex_philo(node_philo);
// 		return (true);
// 	}
// 	x_unlock_mutex_philo(node_philo);
// 	return (false);
// }

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

static void	*put_sleep_think(void *ptr)
{
	t_philo_node	*node_philo;
	long			time_sleep;

	// printf("---- put 1\n");
	node_philo = (t_philo_node *)ptr;
	time_sleep = node_philo->ph->argv[4];
	// x_lock_mutex_philo(node_philo);
	// node_philo->flag_sleeping = true;
	// x_unlock_mutex_philo(node_philo);
	// printf("---- put 2\n");
	if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
		return (ptr);
	if (!put_state(THINKING, node_philo, 0, node_philo->id))
		return (ptr);
	// x_lock_mutex_philo(node_philo);
	// // printf("---- put 3\n");
	// node_philo->flag_sleeping = false;
	// x_unlock_mutex_philo(node_philo);
	return (ptr);
}
