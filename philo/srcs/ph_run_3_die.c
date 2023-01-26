/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_die.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 23:56:48 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	judge_time_to_die(t_ph *ph, size_t num_people);
static bool	check_time_to_die(t_philo *philo_n);
static void	set_flag_died(t_ph *ph, size_t id);
static void	put_died_in_mutex(t_ph *ph, size_t num_people);

void	*run_monitor_die(void *ptr)
{
	t_monitor	*die_monitor;
	t_ph		*ph;
	size_t		num_people;

	die_monitor = (t_monitor *)ptr;
	ph = die_monitor->ph;
	num_people = die_monitor->num_people;
	while (!is_end(&ph->end_st, &ph->mtx_st))
	{
		if (judge_time_to_die(ph, num_people))
			break ;
	}
	put_died_in_mutex(ph, num_people);
	return (ptr);
}

static bool	judge_time_to_die(t_ph *ph, size_t num_people)
{
	size_t	i;
	t_philo	*philo_n;

	i = 0;
	while (i < num_people)
	{
		philo_n = get_philo(&ph->philo_list, i);
		x_lock_mtx_philo(philo_n, &philo_n->mtx_philo);
		if (check_time_to_die(philo_n))
		{
			x_unlock_mtx_philo(philo_n, &philo_n->mtx_philo);
			return (true);
		}
		x_unlock_mtx_philo(philo_n, &philo_n->mtx_philo);
		i++;
	}
	return (false);
}

static void	put_died_in_mutex(t_ph *ph, size_t num_people)
{
	size_t		i;
	t_philo		*philo_n;

	i = 0;
	while (i < num_people)
	{
		philo_n = get_philo(&ph->philo_list, i);
		x_lock_mtx_philo(philo_n, &philo_n->mtx_put);
		i++;
	}
	if (!put_died(ph))
		set_err_num_ph(ph, ERR_PUT_DIED);
	i = 0;
	while (i < num_people)
	{
		philo_n = get_philo(&ph->philo_list, i);
		x_unlock_mtx_philo(philo_n, &philo_n->mtx_put);
		i++;
	}
	return ;
}

static bool	check_time_to_die(t_philo *philo_n)
{
	long	eating;
	long	time_to_die;
	long	elapsed_time;

	eating = philo_n->time[EATING];
	time_to_die = (long)philo_n->ph->argv[2];
	if (!get_time_from_start(philo_n->ph, &elapsed_time))
		return (false);
	if (eating == 0 && elapsed_time >= time_to_die)
	{
		set_flag_died(philo_n->ph, philo_n->id);
		return (true);
	}
	if (eating > 0 && (elapsed_time - eating) >= time_to_die)
	{
		set_flag_died(philo_n->ph, philo_n->id);
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
