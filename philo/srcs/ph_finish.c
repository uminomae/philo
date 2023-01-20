/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:41:46 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	x_pthread_mutex_destroy(t_ph *ph, pthread_mutex_t *mutex);

bool	destroy_mutex(t_ph *ph)
{
	size_t		i;
	size_t		num_people;
	t_fork		*node_fork;	
	t_philo		*node_philo;
	size_t		ret;

	ret = true;
	ret &= x_pthread_mutex_destroy(ph, &ph->mutex_struct.mutex_cnt_ate);
	ret &= x_pthread_mutex_destroy(ph, &ph->mutex_struct.mutex_ate_all);
	ret &= x_pthread_mutex_destroy(ph, &ph->mutex_struct.mutex_die);
	ret &= x_pthread_mutex_destroy(ph, &ph->mutex_struct.mutex_end);
	ret &= x_pthread_mutex_destroy(ph, &ph->mutex_ph);
	node_philo = ph->philo_list.head;
	node_fork = ph->fork_list.head;
	num_people = ph->argv[1];
	i = 0;
	while (i < num_people)
	{
		ret &= x_pthread_mutex_destroy(ph, &node_fork->mutex_fork);
		node_fork = node_fork->next;
		ret &= x_pthread_mutex_destroy(ph, &node_philo->mutex_philo);
		node_philo = node_philo->next;
		i++;
	}
	return (ret);
}

static bool	x_pthread_mutex_destroy(t_ph *ph, pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_destroy(mutex);
	if (ret != 0)
	{
		get_err_num_ph(ph, ERR_PTHREAD_DESTROY);
		return (false);
	}
	return (true);
}

void	end_philo(t_ph *ph)
{
	destroy_mutex(ph);
	free_all(ph);
}

void	end_error(t_ph *ph)
{
	printf("%s", ERR_STR);
	destroy_mutex(ph);
	free_all(ph);
}
