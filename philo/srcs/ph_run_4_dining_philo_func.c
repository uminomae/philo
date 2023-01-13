/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_dining_philo_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 20:46:37 by uminomae         ###   ########.fr       */
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
	if (is_required_times_ate(node_philo, node_philo->cnt))
	{
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
}

bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct)
{
	bool ret;

	ret = false;
	x_lock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	if (end_struct->flag_end == true)
		ret = true;
	x_unlock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	// x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	return (ret);
}

void	run_rutine_philo_dining(t_philo_main *ph, t_philo_node	*node_philo, t_fork_node *node_fork)
{
	bool	end;
	const long time_eat = ph->argv[3];
	const long time_sleep = ph->argv[4];
	t_mutex *mutex_struct;
	t_end_struct *end_struct;

	mutex_struct = &ph->mutex_struct;
	end_struct = &ph->end_struct;
	end = false;
	while (end == false)
	{
		end = is_end(end_struct, mutex_struct);
		
		run_eating(node_philo, node_fork, node_philo->id, time_eat);
		
		if (ph->flag_must_eat == true)
			count_ate_in_philo(node_philo);

		end = is_end(end_struct, mutex_struct);

		// x_lock_mutex_philo(node_monitor->node_philo);
		put_state(SLEEPING, node_philo, time_sleep, node_philo->id);

		end = is_end(end_struct, mutex_struct);

		put_state(THINKING, node_philo, 0, node_philo->id);
	}
}

void	*run_rutine_philo(void *ptr)
{
	t_philo_node	*node_philo;
	t_fork_node		*node_fork;

	node_philo = (t_philo_node *)ptr;
	node_fork = get_fork_node(&node_philo->ph->fork_list, node_philo->id);
	if (node_philo->ph->argv[1] == 1)
		run_case_1person(node_philo);
	else
		run_rutine_philo_dining(node_philo->ph, node_philo, node_fork);
		// run_rutine_philo_dining(node_philo, node_fork);
	return (NULL);
}
