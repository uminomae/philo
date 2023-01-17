/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 03:23:41 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	x_pthread_mutex_destroy(t_philo_main *ph, pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_destroy(mutex);
	if (ret != 0)
		get_err_num_ph(ph, ERR_PTHREAD_DESTROY);
}

void	destroy_mutex(t_philo_main *ph)
{
	size_t		i;
	size_t		num_people;
	t_fork_node	*node_fork;	

	node_fork = ph->fork_list.head;
	num_people = ph->argv[1];
	x_pthread_mutex_destroy(ph, &ph->mutex_struct.mutex_cnt_ate);
	x_pthread_mutex_destroy(ph, &ph->mutex_struct.mutex_ate_all);
	x_pthread_mutex_destroy(ph, &ph->mutex_struct.mutex_die);
	i = 0;
	while (i < num_people)
	{
		x_pthread_mutex_destroy(ph, &node_fork->mutex_fork);
		node_fork = node_fork->next;
		i++;
	}
}

void	end_philo(t_philo_main *ph)
{
	destroy_mutex(ph);
	free_all(ph);
}

void	end_error(t_philo_main *ph)
{
	printf("%s", ERR_STR);
	destroy_mutex(ph);
	free_all(ph);
}
