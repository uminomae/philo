/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_judge_thread.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 00:18:04 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool wait_required_time(t_philo_main *ph, long total, long current)
{
	if (total - current > 5)
	{
		if(!x_usleep_millisec(ph, (total - current) / 2))
			return (false);
	}
	return (true);
}

void	*run_judge_hungry(void *ptr)
{
	t_philo_node	*node_philo;
	long	not_hungry_time;
	long	total;
	long	current;

	node_philo = (t_philo_node *)ptr;
	x_lock_mutex_philo(node_philo);
	not_hungry_time = node_philo->ph->argv[3] + node_philo->ph->argv[4];
	total = not_hungry_time + node_philo->time[EATING];
	x_unlock_mutex_philo(node_philo);
	if(!gettimeofday_millisec(node_philo->ph, &current))
		return (ptr);
	while(total > current)
	{
		wait_required_time(node_philo->ph, total, current);
		if(!gettimeofday_millisec(node_philo->ph, &current))
			return (ptr);
	}
	x_lock_mutex_philo(node_philo);
	node_philo->hungry = true;
	x_unlock_mutex_philo(node_philo);
	return (ptr);
}
