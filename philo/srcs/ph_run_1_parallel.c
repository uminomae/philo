/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_1_parallel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 18:01:06 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	create_thread(t_philo_main *ph, size_t num_people);
static bool	join_pthread(t_philo_main *ph);

bool	run_parallel_process(t_philo_main *ph)
{
	if (!init_mutex(ph))
		return (false);
	if (!create_thread(ph, ph->argv[1]))
		return (false);
	if (!join_pthread(ph))
		return (false);
	if (is_error(ph))
		return (false);
	return (true);
}


static bool	create_thread(t_philo_main *ph, size_t num_people)
{
	size_t			i;
	t_philo_node	*node_philo;

	if (!gettimeofday_millisec(ph, &ph->start_time))
		return (false);
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		x_pthread_create(ph, &node_philo->philo_th, \
					run_rutine_philo, node_philo);
		i++;
	}
	x_pthread_create(ph, &ph->monitor_node.monitor_th, \
				run_rutine_monitor, &ph->monitor_node);
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
