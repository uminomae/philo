/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/12 07:27:58 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	x_pthread_mutex_init(t_philo_main *ph, pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret != 0)
		get_err_flag(ph);
}

void	init_mutex(t_philo_main *ph)
{
	size_t		i;
	size_t		num_people;
	t_fork_node	*node_fork;	

	node_fork = ph->fork_list.head;
	num_people = ph->argv[1];
	x_pthread_mutex_init(ph, &ph->mutex_struct.mutex_cnt_ate);
	x_pthread_mutex_init(ph, &ph->mutex_struct.mutex_ate_all);
	x_pthread_mutex_init(ph, &ph->mutex_struct.mutex_die);
	x_pthread_mutex_init(ph, &ph->mutex_struct.mutex_time_eat_start);
	i = 0;
	while (i < num_people)
	{
		x_pthread_mutex_init(ph, &node_fork->mutex_fork);
		node_fork = node_fork->next;
		i++;
	}
}
