/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_1_parallel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 14:45:01 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_pthread(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;
	int				ret;
	t_philo_node	*node_th;
	t_monitor_node	*node_monitor;

	num_people = ph->argv[1];
	i = 0;
	while (i < num_people)
	{
		node_th = get_philo_node(&ph->philo_list, i);
		ret = pthread_join(node_th->philo_th, NULL);
		if (ret != 0)
			get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		i++;
	}
	i = 0;
	while (i < num_people)
	{
		node_monitor = get_monitor_node(&ph->monitor_list, i);
		ret = pthread_join(node_monitor->monitor_th, NULL);
		if (ret != 0)
			get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		i++;
	}
}

//create thread num_people and monitor
void	run_parallel_process(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;

	num_people = ph->argv[1];
	i = 0;
	get_start_time(ph);
	while (i < num_people)
	{
		set_and_run_philo(ph, i);
		set_and_run_monitor(ph, i);
		i++;
	}
	while (1)
	{
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		if (ph->flag_end == true)
			join_pthread(ph);
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	}
	if (ph->died_struct.died_flag == true)
		put_stamp(get_time_milli_sec() - ph->start_time, ph->died_struct.died_id, DIED_STR);
}
