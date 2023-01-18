/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 18:46:42 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	judge_ate_all(t_philo_main *ph, size_t num_people);
static bool	check_hungry(t_philo_main *ph, size_t num_people);
static int	check_time_ate(t_philo_main *ph, t_philo_node *node_philo);
static bool	put_died(t_philo_main *ph);

void	*run_rutine_monitor(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	size_t			num_people;

	node_monitor = (t_monitor_node *)ptr;
	ph = node_monitor->ph;
	num_people = node_monitor->num_people;
	while (!is_end(&ph->end_struct, &ph->mutex_struct))
	{
		if (ph->flag_must_eat == true)
		{
			if (judge_ate_all(ph, num_people))
				break ;
		}
		if (judge_time_to_die(ph, num_people))
			break ;
		check_hungry(ph, num_people);
	}
	if (!put_died(ph))
		return (NULL);
	return (ptr);
}

static bool	judge_ate_all(t_philo_main *ph, size_t num_people)
{
	t_mutex	*mutex_struct;

	mutex_struct = &ph->mutex_struct;
	x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt >= num_people && ph->ate_struct.ate_all == false)
	{
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, &ph->mutex_struct);
		if (!x_usleep_millisec(ph, ph->argv[3]))
			return (false);
		x_lock_mutex_struct(&mutex_struct->mutex_ate_all, &ph->mutex_struct);
		ph->ate_struct.ate_all = true;
		x_unlock_mutex_struct(&mutex_struct->mutex_ate_all, &ph->mutex_struct);
		x_lock_mutex_struct(&mutex_struct->mutex_end, &ph->mutex_struct);
		ph->end_struct.flag_end = true;
		x_unlock_mutex_struct(&mutex_struct->mutex_end, &ph->mutex_struct);
		return (true);
	}
	x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, &ph->mutex_struct);
	return (false);
}

static bool	check_hungry(t_philo_main *ph, size_t num_people)
{
	size_t			i;
	t_philo_node	*node_philo;
	bool			ret;

	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		ret = check_time_ate(ph, node_philo);
		if (ret == HUNGRY)
			node_philo->hungry = true;
		else
			node_philo->hungry = false;
		x_unlock_mutex_philo(node_philo);
		i++;
	}
	return (true);
}

static int	check_time_ate(t_philo_main *ph, t_philo_node *node_philo)
{
	long	elapsed_time;
	long	hungry_time;

	if (!get_time_from_start(ph, &elapsed_time))
		return (ERR_NEGA_NUM);
	hungry_time = (long)ph->argv[3] * 2 + LIMIT_HUNGRY;
	if (node_philo->time[EATING] == 0)
	{
		if (elapsed_time > hungry_time)
			return (HUNGRY);
	}
	else if (elapsed_time > node_philo->time[EATING] + hungry_time)
		return (HUNGRY);
	return (OK);
}

static bool	put_died(t_philo_main *ph)
{
	long	elapsed_time;

	x_lock_mutex_struct(&ph->mutex_struct.mutex_die, &ph->mutex_struct);
	if (ph->died_struct.died_flag)
	{
		if (!get_time_from_start(ph, &elapsed_time))
			return (false);
		if (!put_stamp(elapsed_time, ph->died_struct.died_id, DIED_STR))
			return (false);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_die, &ph->mutex_struct);
	return (true);
}
