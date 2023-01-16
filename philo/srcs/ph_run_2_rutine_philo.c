/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 02:50:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
static bool	is_awake(t_philo_node *node_philo);
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
	const long	sleep_time = node_philo->time[EATING] + node_philo->ph->argv[4];
	long		current;

	if (node_philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		while (!is_awake(node_philo))
		{
			if (is_end(&ph->end_struct, &ph->mutex_struct))
				return ;
			if (!gettimeofday_millisec(node_philo->ph, &current))
				return ;
			wait_required_time(node_philo->ph, sleep_time, current);
		}
		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			return ;
		if (ph->flag_must_eat == true)
			count_ate_in_philo(node_philo);
		x_pthread_create(ph, &node_philo->philo_sleep_th, \
						put_sleep_think, node_philo);
		if (!x_pthread_detach(ph, &node_philo->philo_sleep_th))
			return ;
	}
	return ;
}

static bool	is_awake(t_philo_node *node_philo)
{
	x_lock_mutex_philo(node_philo);
	if (node_philo->flag_sleeping == false)
	{
		x_unlock_mutex_philo(node_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_philo);
	return (false);
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

static void	*put_sleep_think(void *ptr)
{
	t_philo_node	*node_philo;
	long			time_sleep;

	node_philo = (t_philo_node *)ptr;
	time_sleep = node_philo->ph->argv[4];
	x_lock_mutex_philo(node_philo);
	node_philo->flag_sleeping = true;
	x_unlock_mutex_philo(node_philo);
	if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
		return (ptr);
	x_lock_mutex_philo(node_philo);
	node_philo->flag_sleeping = false;
	x_unlock_mutex_philo(node_philo);
	if (!put_state(THINKING, node_philo, 0, node_philo->id))
		return (ptr);
	return (ptr);
}
