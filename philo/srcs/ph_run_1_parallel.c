/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_1_parallel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/16 03:56:36 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool create_thread(t_philo_main *ph, size_t num_people);
static bool	join_pthread(t_philo_main *ph);
static void put_died(t_philo_main *ph);

bool run_parallel_process(t_philo_main *ph)
{
	if (!create_thread(ph, ph->argv[1]))
		return (false);
	if (!join_pthread(ph))
		return (false);
	put_died(ph);
	return (true);
}

t_philo_node	*set_and_run_philo(t_philo_main *ph, size_t id)
{
	t_philo_node	*node_philo;

	node_philo = get_philo_node(&ph->philo_list, id);
	node_philo->id = id;
	node_philo->flag_must_eat = ph->flag_must_eat;
	node_philo->times_must_eat = ph->argv[5];
	node_philo->hungry = true;
	if (id % 2 == 1)
		usleep(1000);
	return (node_philo);
}

static bool create_thread(t_philo_main *ph, size_t num_people)
{
	size_t	i;
	int 	ret;
	t_philo_node	*node_philo;

	i = 0;
	while (i < num_people)
	{
		node_philo = set_and_run_philo(ph, i);
		ret = pthread_create(&node_philo->philo_th, NULL, \
							run_rutine_philo, node_philo);
		if (ret != 0)
			get_err_num_ph(node_philo->ph, ERR_PTHREAD_CREATE);
		i++;
	}
	ret = pthread_create(&ph->monitor_node.monitor_th, NULL, \
				run_rutine_monitor, &ph->monitor_node);
	if (ret != 0)
		get_err_num_ph(ph, ERR_PTHREAD_CREATE);
	if (ph->error_num > NUM_ERR_LOW)
		return (false);
	return (true);
}

static bool	join_pthread(t_philo_main *ph)
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
	if (ph->error_num > NUM_ERR_LOW)
		return (false);
	return (true);
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
