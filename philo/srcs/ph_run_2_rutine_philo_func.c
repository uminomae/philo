/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/16 21:39:28 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
static void	run_case_1person(t_philo_node	*node_philo, t_fork_node *node_fork);
static void	count_ate_in_philo(t_philo_node *node_philo);
// static bool	is_required_times_ate(t_philo_node *node_th, size_t cnt);


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

static void	run_case_1person(t_philo_node	*node_philo, t_fork_node *node_fork)
{
	x_lock_mutex_fork(node_fork);
	if (!put_state(TAKEN_FORK, node_philo, 0, node_philo->id))
	{
		x_unlock_mutex_fork(node_fork);
		return ;
	}
	x_unlock_mutex_fork(node_fork);
	usleep(node_philo->ph->argv[2] * 1000);
	x_lock_mutex_philo(node_philo);
	set_flag_died(node_philo->ph, node_philo->id);
	x_unlock_mutex_philo(node_philo);
	return ;
}
void *put_sleep_think(void *ptr)
{
	t_philo_node	*node_philo;
	long time_sleep;

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

static bool	is_awake(t_philo_node *node_philo)
{
	x_lock_mutex_philo(node_philo);
	if (node_philo->flag_sleeping == false)
	{
		x_unlock_mutex_philo(node_philo);
		return (true) ;
	}
	x_unlock_mutex_philo(node_philo);
	return (false);
}


// bool x_pthread_detach(t_philo_main *ph,  pthread_t *thread)
// {
// 	int	ret;

// 	ret = pthread_detach(*thread);
// 	if (ret != 0)
// 	{
// 		get_err_num_ph(ph, ERR_PTHREAD_DETACH);
// 		return (false);
// 	}
// 	return (true);
// }

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, t_fork_node *node_fork)
{
	const long time_eat = ph->argv[3];

	if (node_philo->id % 2 == 1)
		usleep(100);
	while (1)
	{
		while(1)
		{
			if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
				return ;
			if (is_awake(node_philo))
				break ;
		}
		if (!run_eating(node_philo, node_fork, node_philo->id, time_eat))
			break ;
		if (ph->flag_must_eat == true)
			count_ate_in_philo(node_philo);
		x_pthread_create(ph, &node_philo->philo_sleep_th, put_sleep_think, node_philo);
		x_pthread_detach(ph, &node_philo->philo_sleep_th);
	}
	return ;
}

static void	count_ate_in_philo(t_philo_node *node_philo)
{
	t_mutex	*mutex_struct;

	mutex_struct = &node_philo->ph->mutex_struct;
	x_lock_mutex_philo(node_philo);
	// if (is_required_times_ate(node_philo, node_philo->cnt))
	if (node_philo->times_must_eat == node_philo->cnt)
	{
		x_unlock_mutex_philo(node_philo);
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
	x_unlock_mutex_philo(node_philo);
}

// static bool	is_required_times_ate(t_philo_node *node_th, size_t cnt)
// {
// 	if (node_th->times_must_eat == cnt)
// 		return (true);
// 	return (false);
// }

// static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, t_fork_node *node_fork)
// {
// 	const long time_eat = ph->argv[3];
// 	// const long time_sleep = ph->argv[4];
// 	int	ret;
	
// 	ret = 0;
// 	if (node_philo->id % 2 == 1)
// 		usleep(100);
// 	while (1)
// 	{
// 		while(1)
// 		{
// 			if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
// 				return ;
// 			x_lock_mutex_philo(node_philo);
// 			if (node_philo->flag_sleeping == false)
// 			{
// 				x_unlock_mutex_philo(node_philo);
// 				break;
// 			}
// 			x_unlock_mutex_philo(node_philo);
// 		// ret = usleep(100);
// 		// if (ret < 0)
// 		// 	return(ERR_NEGA_NUM);
// 		}
// 		if (!run_eating(node_philo, node_fork, node_philo->id, time_eat))
// 			break ;
// 		if (ph->flag_must_eat == true)
// 		{
// 		// printf("------a\n");
// 			count_ate_in_philo(node_philo);
// 		}
// 		x_pthread_create(ph, &node_philo->philo_sleep_th, put_sleep_think, node_philo);

// 		// ret = pthread_create(&node_philo->philo_sleep_th, NULL, \
// 		// 		put_sleep_think, node_philo);
// 		// if (ret != 0)
// 		// 	get_err_num_ph(node_philo->ph, ERR_PTHREAD_CREATE);

// 		//err　処理
// 		ret = pthread_detach(node_philo->philo_sleep_th);
// 		if (ret != 0)
// 			get_err_num_ph(ph, ERR_PTHREAD_DETACH);
// 		// if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
// 		// 	break;
// 		// if (!put_state(THINKING, node_philo, 0, node_philo->id))
// 		// 	break;
// 	}
// 	return ;
// }