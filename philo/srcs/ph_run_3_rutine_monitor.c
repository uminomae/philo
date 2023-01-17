/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_3_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 02:20:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct);
bool	judge_ate_all(t_philo_main *ph, size_t num_people);

	// if (!x_usleep(ph, 100))
	// 	return (false);
static bool	put_died(t_philo_main *ph)
{
	long	cur_time;

	x_lock_mutex_struct(&ph->mutex_struct.mutex_die, &ph->mutex_struct);
	if (ph->died_struct.died_flag)
	{
		cur_time = get_time_from_start(ph);
		if (cur_time == ERR_NEGA_NUM)
			return (false);
		put_stamp(cur_time, ph->died_struct.died_id, DIED_STR);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_die, &ph->mutex_struct);
	return (true);
}

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
	if(!put_died(ph))
		return (NULL);
	return (ptr);
}

bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct)
{
	bool	ret;

	ret = false;
	x_lock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	if (end_struct->flag_end == true)
		ret = true;
	x_unlock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	return (ret);
}

bool	judge_ate_all(t_philo_main *ph, size_t num_people)
{
	t_mutex	*mutex_struct;

	mutex_struct = &ph->mutex_struct;
	x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt >= num_people && ph->ate_struct.ate_all == false)
	{
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, &ph->mutex_struct);
		usleep(ph->argv[3] * 1000);
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
