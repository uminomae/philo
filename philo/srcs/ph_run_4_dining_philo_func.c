/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_dining_philo_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 14:45:19 by uminomae         ###   ########.fr       */
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

bool	is_required_times_ate(t_philo_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == true && \
		node_th->times_must_eat == cnt)
		return (true);
	return (false);
}

void	count_ate_in_philo(t_philo_node *node_philo)
{
	t_mutex				*mutex_struct;

	mutex_struct = &node_philo->ph->mutex_struct;
	// printf("--------- cnt philo %zu\n", node_philo->cnt);
	if (is_required_times_ate(node_philo, node_philo->cnt))
	{
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		// node_philo->ate == true;
		// printf("======cnt_mustate_person %zu id:%zu\n", node_philo->ph->ate_struct.ate_cnt, node_philo->ph->id);
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
}

void	run_rutine_philo(t_philo_node	*node_philo, t_fork_node *node_fork)
{
	const long time_eat = node_philo->ph->argv[3];
	const long time_sleep = node_philo->ph->argv[4];
	while (1)
	{
		// judge end flag 
		// x_lock_mutex_philo(node_philo);
		// if (node_philo->flag_end == true)
		// {
		// 	x_unlock_mutex_philo(node_philo);
		// 	break ;
		// }
		// x_unlock_mutex_philo(node_philo);

		// wait_ate_person(node_philo);

		// x_lock_mutex_philo(node_philo);
		run_eating(node_philo, node_fork, node_philo->id, time_eat);
		count_ate_in_philo(node_philo);
		// x_unlock_mutex_philo(node_philo);

		x_lock_mutex_philo(node_philo);
		put_state(SLEEPING, node_philo, time_sleep, node_philo->id);
		x_unlock_mutex_philo(node_philo);

		x_lock_mutex_philo(node_philo);
		put_state(THINKING, node_philo, 0, node_philo->id);
		x_unlock_mutex_philo(node_philo);
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
