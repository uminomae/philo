/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_2_die_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:53:17 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_time_to_die(t_philo *node_philo);

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

void	set_flag_died(t_ph *ph, size_t id)
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

void	set_flag_end(t_ph *ph, \
			pthread_mutex_t *mtx_end, t_mutex *mtx_st)
{
	x_lock_mutex_struct(mtx_end, mtx_st);
	ph->end_st.flag_end = true;
	x_unlock_mutex_struct(mtx_end, mtx_st);
}

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