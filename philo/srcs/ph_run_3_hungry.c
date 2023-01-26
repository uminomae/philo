/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_hungry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:48:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	judge_hungry(t_ph *ph, size_t num_people);
static int	check_time_ate(t_ph *ph, t_philo *philo_n);

void	*run_monitor_hungry(void *ptr)
{
	t_monitor	*hungry_monitor;
	t_ph		*ph;
	size_t		num_people;

	hungry_monitor = (t_monitor *)ptr;
	ph = hungry_monitor->ph;
	num_people = hungry_monitor->num_people;
	while (!is_end(&ph->end_st, &ph->mtx_st))
	{
		if (!judge_hungry(ph, num_people))
			set_flag_end(ph, &ph->mtx_st.mtx_end, &ph->mtx_st);
	}
	return (ptr);
}

static bool	judge_hungry(t_ph *ph, size_t num_people)
{
	size_t	i;
	t_philo	*philo_n;
	int		ret;

	i = 0;
	while (i < num_people)
	{
		philo_n = get_philo(&ph->philo_list, i);
		x_lock_mtx_philo(philo_n, &philo_n->mtx_philo);
		ret = check_time_ate(ph, philo_n);
		if (ret == HUNGRY)
			philo_n->hungry = true;
		else if (ret == ERR_NEGA_NUM)
		{
			x_unlock_mtx_philo(philo_n, &philo_n->mtx_philo);
			return (false);
		}
		else
			philo_n->hungry = false;
		x_unlock_mtx_philo(philo_n, &philo_n->mtx_philo);
		i++;
	}
	return (true);
}

static int	check_time_ate(t_ph *ph, t_philo *philo_n)
{
	long	limit;
	long	elapsed_time;

	if (!get_time_from_start(ph, &elapsed_time))
		return (ERR_NEGA_NUM);
	limit = (long)ph->argv[2] * 3 / 4;
	if (philo_n->time[EATING] == 0)
	{
		if (elapsed_time > limit)
			return (HUNGRY);
	}
	else if (elapsed_time > philo_n->time[EATING] + limit)
		return (HUNGRY);
	return (OK);
}
