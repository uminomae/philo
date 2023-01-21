/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/21 09:26:28 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	judge_ate_all(t_ph *ph, size_t num_people);
static bool	check_hungry(t_ph *ph, size_t num_people);
static int	check_time_ate(t_ph *ph, t_philo *node_philo);

void	*run_rutine_monitor(void *ptr)
{
	t_monitor	*monitor;
	t_ph		*ph;
	size_t		num_people;

	monitor = (t_monitor *)ptr;
	ph = monitor->ph;
	num_people = monitor->num_people;
	while (!is_end(&ph->end_struct, &ph->mtx_st))
	{
		// if (ph->flag_must_eat == true)
		if (monitor->flag_must_eat == true)
		{
			if (judge_ate_all(ph, num_people))
				break ;
		}
		if (judge_time_to_die(ph, num_people))
			break ;
		if (!check_hungry(ph, num_people))
			set_flag_end(ph, &ph->mtx_st.mtx_end, &ph->mtx_st);
		if (is_error(ph))
			set_flag_end(ph, &ph->mtx_st.mtx_end, &ph->mtx_st);
	}
	return (ptr);
}

static bool	judge_ate_all(t_ph *ph, size_t num_people)
{
	t_mutex	*mtx_st;

	mtx_st = &ph->mtx_st;
	x_lock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
	if (ph->ate_struct.ate_cnt >= num_people && ph->ate_struct.ate_all == false)
	{
		x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
		if (!x_usleep_millisec(ph, ph->argv[3]))
			return (false);
		x_lock_mutex_struct(&mtx_st->mtx_ate_all, &ph->mtx_st);
		ph->ate_struct.ate_all = true;
		x_unlock_mutex_struct(&mtx_st->mtx_ate_all, &ph->mtx_st);
		x_lock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
		ph->end_struct.flag_end = true;
		x_unlock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
		return (true);
	}
	x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, &ph->mtx_st);
	return (false);
}

static bool	check_hungry(t_ph *ph, size_t num_people)
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

static int	check_time_ate(t_ph *ph, t_philo *node_philo)
{
	long	eat_time;
	long	limit;
	long	elapsed_time;

	if (!get_time_from_start(ph, &elapsed_time))
		return (ERR_NEGA_NUM);
	eat_time = (long)ph->argv[3];
	limit = eat_time * 2 + eat_time / 4;
	if (node_philo->time[EATING] == 0)
	{
		if (elapsed_time > limit)
			return (HUNGRY);
	}
	else if (elapsed_time > node_philo->time[EATING] + limit)
		return (HUNGRY);
	return (OK);
}
