/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/24 03:25:48 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	judge_time_to_die(t_ph *ph, size_t num_people);
static bool	check_time_to_die(t_philo *node_philo);
static void	set_flag_died(t_ph *ph, size_t id);

void	*run_monitor_die(void *ptr)
{
	t_monitor	*die_monitor;
	t_ph		*ph;
	size_t		num_people;
	size_t		i;
	t_philo		*node_philo;

	die_monitor = (t_monitor *)ptr;
	ph = die_monitor->ph;
	num_people = die_monitor->num_people;
	while (!is_end(&ph->end_st, &ph->mtx_st))
	{
		if (judge_time_to_die(ph, num_people))
			break ;
	}
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		i++;
	}
	if (!put_died(ph))
		return (NULL);
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo(&ph->philo_list, i);
		x_unlock_mutex_philo(node_philo);
		i++;
	}
	return (ptr);
}

static bool	judge_time_to_die(t_ph *ph, size_t num_people)
{
	size_t	i;
	t_philo	*node_philo;

	i = 0;
	while (i < num_people)
	{
		x_lock_mutex_philo(ph->philo_list.head);
		node_philo = get_philo(&ph->philo_list, i);
		x_unlock_mutex_philo(ph->philo_list.head);
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

static void	set_flag_died(t_ph *ph, size_t id)
{
	t_mutex	*mtx_st;

	mtx_st = &ph->mtx_st;

	x_lock_mutex_struct(&mtx_st->mtx_die, mtx_st);
	if (ph->died_st.died_flag == false)
	{
		ph->died_st.died_flag = true;
		ph->died_st.died_id = id;
	}
	x_unlock_mutex_struct(&mtx_st->mtx_die, mtx_st);
	x_lock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
	ph->end_st.flag_end = true;
	x_unlock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
}
