/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_1_eat_hungry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:52:48 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	judge_ate_all(t_ph *ph, size_t num_people)
{
	t_mutex	*mtx_st;

	mtx_st = &ph->mtx_st;
	x_lock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
	if (ph->ate_st.ate_cnt >= num_people && ph->ate_st.ate_all == false)
	{
		x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
		if (!x_usleep_millisec(ph, ph->argv[3]))
			return (false);
		x_lock_mutex_struct(&mtx_st->mtx_ate_all, &ph->mtx_st);
		ph->ate_st.ate_all = true;
		x_unlock_mutex_struct(&mtx_st->mtx_ate_all, &ph->mtx_st);
		x_lock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
		ph->end_st.flag_end = true;
		x_unlock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
		return (true);
	}
	x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
	return (false);
}


bool	judge_hungry(t_ph *ph, size_t num_people)
{
	size_t	i;
	t_philo	*node_philo;
	int		ret;

	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		ret = check_time_ate(ph, node_philo);
		if (ret == HUNGRY)
			node_philo->hungry = true;
		else if (ret == ERR_NEGA_NUM)
		{
			x_unlock_mutex_philo(node_philo);
			return (false);
		}
		else
			node_philo->hungry = false;
		x_unlock_mutex_philo(node_philo);
		i++;
	}
	return (true);
}

int	check_time_ate(t_ph *ph, t_philo *node_philo)
{
	long	limit;
	long	elapsed_time;

	if (!get_time_from_start(ph, &elapsed_time))
		return (ERR_NEGA_NUM);
	limit = (long)ph->argv[2] * 3 / 4;
	if (node_philo->time[EATING] == 0)
	{
		if (elapsed_time > limit)
			return (HUNGRY);
	}
	else if (elapsed_time > node_philo->time[EATING] + limit)
		return (HUNGRY);
	return (OK);
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
