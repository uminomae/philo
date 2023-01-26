/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 23:03:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	x_pthread_mutex_destroy(t_ph *ph, pthread_mutex_t *mutex);

bool	destroy_mutex(t_ph *ph)
{
	size_t		i;
	t_fork		*fork_n;	
	t_philo		*philo_n;
	size_t		ret;

	ret = true;
	ret &= x_pthread_mutex_destroy(ph, &ph->mtx_st.mtx_cnt_ate);
	ret &= x_pthread_mutex_destroy(ph, &ph->mtx_st.mtx_die);
	ret &= x_pthread_mutex_destroy(ph, &ph->mtx_st.mtx_end);
	ret &= x_pthread_mutex_destroy(ph, &ph->mutex_ph);
	philo_n = ph->philo_list.head;
	fork_n = ph->fork_list.head;
	i = 0;
	while (i < ph->argv[1])
	{
		ret &= x_pthread_mutex_destroy(ph, &fork_n->mtx_fork);
		fork_n = fork_n->next;
		ret &= x_pthread_mutex_destroy(ph, &philo_n->mtx_philo);
		ret &= x_pthread_mutex_destroy(ph, &philo_n->mtx_put);
		philo_n = philo_n->next;
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
		set_err_num_ph(ph, ERR_PTHREAD_DESTROY);
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
