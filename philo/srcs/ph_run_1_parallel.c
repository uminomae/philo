/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_1_parallel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 17:25:52 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	join_pthread(t_philo_main *ph)
{
	size_t			i;
	const size_t	num_people = ph->argv[1];
	t_philo_node	*node_philo;
	t_monitor_node	*node_monitor;

	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		if (pthread_join(node_philo->philo_th, NULL) != 0)
			get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		node_monitor = get_monitor_node(&ph->monitor_list, i);
		if (pthread_join(node_monitor->monitor_th, NULL) != 0)
			get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		i++;
	}
}

void create_thread(t_philo_main *ph, size_t num_people)
{
	size_t	i;

	i = 0;
	while (i < num_people)
	{
		set_and_run_philo(ph, i);
		set_and_run_monitor(ph, i);
		i++;
	}
}

//create thread num_people and monitor
void	run_parallel_process(t_philo_main *ph)
{
	size_t	num_people;
	bool	end;

	end = false;
	num_people = ph->argv[1];
	get_start_time(ph);
	create_thread(ph, num_people);
	while (end == false)
	{
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		if (ph->flag_end == true)
			end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	}
	join_pthread(ph);
	// printf("after--join--------------\n");
	if (ph->died_struct.died_flag == true)
		put_stamp(get_time_milli_sec() - ph->start_time, ph->died_struct.died_id, DIED_STR);
}
