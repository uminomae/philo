/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_judge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:08:28 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_time_to_die(t_philo *node_philo);

bool	is_end(t_end *end_st, t_mutex *mtx_st)
{
	bool	ret;

	ret = false;
	x_lock_mutex_struct(&mtx_st->mtx_end, mtx_st);
	if (end_st->flag_end == true)
		ret = true;
	x_unlock_mutex_struct(&mtx_st->mtx_end, mtx_st);
	return (ret);
}

bool	judge_time_to_die(t_ph *ph, size_t num_people)
{
	size_t	i;
	t_philo	*node_philo;

	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo(&ph->philo_list, i);
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

static bool	check_time_to_die(t_philo *node_philo)
{
	long	eating;
	long	time_to_die;
	long	elapsed_time;

	eating = node_philo->time[EATING];
	time_to_die = (long)node_philo->ph->argv[2];
	if (!get_time_from_start(node_philo->ph, &elapsed_time))
		return (false);
	if (eating == 0 && elapsed_time >= time_to_die)
	{
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	if (eating > 0 && (elapsed_time - eating) >= time_to_die)
	{
		set_flag_died(node_philo->ph, node_philo->id);
		return (true);
	}
	return (false);
}

bool	is_hungly(t_philo *node_philo)
{
	t_philo	*node_next_philo;
	t_philo	*node_prev_philo;

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
