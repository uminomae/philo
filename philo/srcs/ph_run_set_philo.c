/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_set_philo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 20:02:14 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_node	*get_philo_node(t_philo_list *list_philo, size_t id)
{
	size_t			i;
	t_philo_node	*node_philo;

	node_philo = list_philo->head;
	i = 0;
	while (i < id)
	{
		node_philo = node_philo->next;
		i++;
	}
	return (node_philo);
}

static void	create_and_run_pthread_philo(t_philo_node *node_th)
{
	int	ret;

	ret = pthread_create(&node_th->thread, NULL, \
		run_dining_philo_in_thread, node_th);
	if (ret != 0)
		get_err_flag_node_th(node_th);
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

void	set_end_flag_to_philo(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;
	t_philo_node	*node_philo;

	num_people = ph->argv[1];
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo_node(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		node_philo->flag_end = true;
		x_unlock_mutex_philo(node_philo);
		i++;
	}
}