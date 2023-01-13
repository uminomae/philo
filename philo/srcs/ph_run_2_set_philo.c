/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_set_philo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 17:53:07 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	create_and_run_pthread_philo(t_philo_node *node_philo)
{
	int	ret;

	ret = pthread_create(&node_philo->philo_th, NULL, \
		run_rutine_dining_in_thread, node_philo);
	if (ret != 0)
		get_err_num_ph(node_philo->ph, ERR_PTHREAD_CREATE);
}

void	set_and_run_philo(t_philo_main *ph, size_t id)
{
	t_philo_node	*node_philo;

	node_philo = get_philo_node(&ph->philo_list, id);
	node_philo->id = id;
	node_philo->start_time = ph->start_time;
	node_philo->flag_must_eat = ph->flag_must_eat;
	node_philo->times_must_eat = ph->argv[5];
	node_philo->mutex_struct = &ph->mutex_struct;
	node_philo->ate_struct = &ph->ate_struct;
	node_philo->died_struct = &ph->died_struct;
	create_and_run_pthread_philo(node_philo);
}
