/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_judge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 18:32:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_time_to_die(t_philo_node *node_philo);

bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct)
{
	bool	ret;

	ret = false;
	x_lock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	if (end_struct->flag_end == true)
		ret = true;
	x_unlock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	return (ret);
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
		if (check_time_to_die(node_philo))
		{
			x_unlock_mutex_philo(node_philo);
			return (true);
		}
		x_unlock_mutex_philo(node_philo);
		i++;
	}
	return (false);
}

static bool	check_time_to_die(t_philo_node *node_philo)
{
	const long	eating = node_philo->time[EATING];
	const long	time_to_die = (long)node_philo->ph->argv[2];
	long		cur_time;

	if(!get_time_from_start(node_philo->ph, &cur_time))
		return (ERR_NEGA_NUM);
	// cur_time = get_time_from_start(node_philo->ph);
	// if (cur_time == ERR_NEGA_NUM)
	// 	return (false);
	if (eating == 0 && cur_time >= time_to_die)
	{
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	if (eating > 0 && (cur_time - eating) >= time_to_die)
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
