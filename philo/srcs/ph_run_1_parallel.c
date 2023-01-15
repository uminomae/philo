/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_1_parallel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 12:27:45 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void create_thread(t_philo_main *ph, size_t num_people);
// static void	wait_end_simulation(t_philo_main *ph);
static void	join_pthread(t_philo_main *ph);
static void put_died(t_philo_main *ph);

void	run_parallel_process(t_philo_main *ph)
{
	size_t	num_people;

	num_people = ph->argv[1];
	create_thread(ph, num_people);
	join_pthread(ph);
	// puts("----------------died");
	put_died(ph);
}

static void create_thread(t_philo_main *ph, size_t num_people)
{
	size_t	i;
	int 	ret;

	i = 0;
	while (i < num_people)
	{
		set_and_run_philo(ph, i);
		i++;
	}
	ret = pthread_create(&ph->monitor_node.monitor_th, NULL, \
							run_rutine_monitor_in_thread, &ph->monitor_node);
	if (ret != 0)
		get_err_num_ph(ph, ERR_PTHREAD_CREATE);
}

static void	join_pthread(t_philo_main *ph)
{
	size_t			i;
	const size_t	num_people = ph->argv[1];
	t_philo_node	*node_philo;

	if (pthread_join(ph->monitor_node.monitor_th, NULL) != 0)
		get_err_num_ph(ph, ERR_PTHREAD_JOIN);
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		if (pthread_join(node_philo->philo_th, NULL) != 0)
			get_err_num_ph(ph, ERR_PTHREAD_JOIN);
		i++;
	}
}

static void put_died(t_philo_main *ph)
{
	long	time;

	if (ph->died_struct.died_flag == true)
	{
		time = get_time_milli_sec();
		put_stamp(time, ph->died_struct.died_id, DIED_STR);
	}
}
