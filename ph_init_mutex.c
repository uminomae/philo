/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 14:22:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	x_pthread_mutex_init(pthread_mutex_t *mutex)
{
	int ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret != 0)
		exit(1);
}

void	init_pthread_mutex(t_philo *ph)
{
	size_t	i;
	size_t	num_philo;
	t_fork_node	*node_fork;

	node_fork = ph->fork_list.head;
	num_philo = ph->argv[1];
	// x_pthread_mutex_init(&ph->food_lock);
	i = 0;
	while (i < num_philo)
	{
		x_pthread_mutex_init(&node_fork->mutex);
		node_fork = node_fork->next;
		i++;
	}
}
