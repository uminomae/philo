/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_judge.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 02:15:35 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_ate_time_to_die(t_philo_node *node_philo);

bool	wait_required_time(t_philo_main *ph, long total, long current)
{
	if (total - current > 5)
	{
		if (!x_usleep_millisec(ph, (total - current) / 2))
			return (false);
	}
	return (true);
}

int	check_time_ate(t_philo_main *ph, t_philo_node *node_philo)
{
	long	cur_time;

	cur_time = get_time_from_start(ph);
	if (cur_time == ERR_NEGA_NUM)
		return (ERR_NEGA_NUM);
	if (node_philo->time[EATING] == 0)
	{
		if (cur_time > (long)ph->argv[3] + (long)ph->argv[3] + LIMIT_HUNGRY)
			return (HUNGRY);
	}
	else if (cur_time > node_philo->time[EATING] + (long)ph->argv[3] + (long)ph->argv[3] + LIMIT_HUNGRY)
		return (HUNGRY);
	return (OK);
}

bool	check_hungry(t_philo_main *ph, size_t num_people)
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


bool	judge_time_to_die(t_philo_main *ph, size_t num_people)
{
	size_t			i;
	t_philo_node	*node_philo;

	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		if (check_ate_time_to_die(node_philo))
		{
			x_unlock_mutex_philo(node_philo);
			return (true);
		}
		x_unlock_mutex_philo(node_philo);
		i++;
	}
	return (false);
}

static bool	check_ate_time_to_die(t_philo_node *node_philo)
{
	const long	eating = node_philo->time[EATING];
	const long	time_to_die = (long)node_philo->ph->argv[2];
	long		cur_time;

	cur_time = get_time_from_start(node_philo->ph);
	if (cur_time == ERR_NEGA_NUM)
		return (false);
	if (eating == 0 && cur_time - node_philo->ph->start_time >= time_to_die)
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
