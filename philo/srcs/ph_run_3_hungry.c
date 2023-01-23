/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_monitor_hungry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 13:26:10 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	judge_hungry(t_ph *ph, size_t num_people);
static int	check_time_ate(t_ph *ph, t_philo *node_philo);

void	*run_monitor_hungry(void *ptr)
{
	t_monitor	*monitor;
	t_ph		*ph;
	size_t		num_people;

	monitor = (t_monitor *)ptr;
	ph = monitor->ph;
	num_people = monitor->num_people;
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
