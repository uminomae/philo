/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_judge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 02:35:00 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_ate_time_to_die(t_philo_node *node_philo);

void	*run_judge_hungry(void *ptr)
{
	t_philo_node	*node_philo;
	long			not_hungry_time;
	long			total;
	long			current;

	node_philo = (t_philo_node *)ptr;
	x_lock_mutex_philo(node_philo);
	not_hungry_time = node_philo->ph->argv[3] + node_philo->ph->argv[4];
	total = not_hungry_time + node_philo->time[EATING];
	x_unlock_mutex_philo(node_philo);
	if (!gettimeofday_millisec(node_philo->ph, &current))
		return (ptr);
	while (total > current)
	{
		wait_required_time(node_philo->ph, total, current);
		if (!gettimeofday_millisec(node_philo->ph, &current))
			return (ptr);
	}
	x_lock_mutex_philo(node_philo);
	node_philo->hungry = true;
	x_unlock_mutex_philo(node_philo);
	return (ptr);
}

bool	wait_required_time(t_philo_main *ph, long total, long current)
{
	if (total - current > 5)
	{
		// if(!x_usleep_millisec(ph, 1000))
		if (!x_usleep_millisec(ph, (total - current) / 2))
			return (false);
	}
	return (true);
}

bool	judge_time_to_die(t_philo_main *ph, size_t num_people)
{
	size_t			i;
	t_philo_node	*node_philo;

	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		if (check_ate_time_to_die(node_philo))
		{
			x_unlock_mutex_philo(node_philo);
			return (true);
		}
		x_unlock_mutex_philo(node_philo);
		i++;
	}
	return (false);
}

static bool	check_ate_time_to_die(t_philo_node *node_philo)
{
	const long	eating = node_philo->time[EATING];
	const long	time_to_die = (long)node_philo->ph->argv[2];
	long		time_current;

	if (!gettimeofday_millisec(node_philo->ph, &time_current))
		return (false);
	// printf("%ld, %ld\n", time_current, node_philo->ph->start_time);
	// printf("%ld, %ld\n", node_philo->time[EATING], time_to_die);
	if (eating == 0 && time_current - node_philo->ph->start_time >= time_to_die)
	{
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	// else if (time_current - eating >= time_to_die)
	if (eating > 0 && time_current - eating >= time_to_die)
	{
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	return (false);
}

void	set_flag_died(t_philo_main *ph, size_t id)
{
	t_mutex	*mutex_struct;

	mutex_struct = &ph->mutex_struct;
	x_lock_mutex_struct(&mutex_struct->mutex_die, mutex_struct);
	if (ph->died_struct.died_flag == false)
	{
		ph->died_struct.died_flag = true;
		ph->died_struct.died_id = id;
	}
	x_unlock_mutex_struct(&mutex_struct->mutex_die, mutex_struct);
	x_lock_mutex_struct(&mutex_struct->mutex_end, &ph->mutex_struct);
	ph->end_struct.flag_end = true;
	x_unlock_mutex_struct(&mutex_struct->mutex_end, &ph->mutex_struct);
}
