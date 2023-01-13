/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 16:55:10 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_finished_ate_last_person(t_philo_node *node_th)
{
	long	time_current;
	long	time_ate;
	long	timeval;
	long	time_to_eat;

	timeval = get_time_milli_sec();
	if (timeval < 0)
		node_th->flag_err = true;
	time_to_eat = node_th->ph->argv[3];
	time_current = timeval - node_th->start_time;
	time_ate = node_th->time[EATING] + time_to_eat;
	if (time_current > time_ate)
		return (true);
	return (false);
}

bool	is_flag_end(t_philo_main *ph)
{
	if (ph->flag_end == true)
		return (true);
	return (false);
}


bool	judge_ate_all(t_philo_main *ph, size_t num_people, t_philo_node *node_philo)
{
	bool wait_time_eating;

	wait_time_eating = false;
	x_lock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt == num_people)
	{
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
		// printf("===============ate_all\n");
		while (wait_time_eating == false)
		{
			if (is_finished_ate_last_person(node_philo) == true)
				wait_time_eating = true;
		}
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		//flag end
		ph->flag_end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		// printf("===============end flag\n");
		
		return (true);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	return (false);
}

//TODO argv[1]をinitでnum_peopleに
void	*run_rutine_monitor_in_thread(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	size_t	num_people;
	long	time_current;
	bool	end;

	end = false;
	node_monitor = (t_monitor_node *)ptr;
	ph = node_monitor->ph;
	num_people = ph->argv[1];
	while (end == false)
	{
		// printf("========moni th\n");
		//ate_all?
		if (ph->flag_must_eat == true)
			judge_ate_all(ph, num_people, node_monitor->node_philo);
		time_current = get_time_milli_sec();
		if (time_current < 0)
			get_err_num_ph(node_monitor->ph, ERR_GETTEIMEOFDAY);
		
		x_lock_mutex_philo(node_monitor->node_philo);
		check_time_to_die(node_monitor->node_philo, time_current);
		x_unlock_mutex_philo(node_monitor->node_philo);

		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		if (ph->flag_end == true)
			end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	}
	return (ptr);
}
