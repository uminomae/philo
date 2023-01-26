/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:39:02 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	x_lock_mutex_philo(t_philo *philo_n, pthread_mutex_t *mtx)
{
	int	ret;

	ret = pthread_mutex_lock(mtx);
	if (ret != 0)
		set_err_num_philo(philo_n, ERR_PTHREAD_LOCK);
}

void	x_unlock_mutex_philo(t_philo *philo_n, pthread_mutex_t *mtx)
{
	int	ret;

	ret = pthread_mutex_unlock(mtx);
	if (ret != 0)
		set_err_num_philo(philo_n, ERR_PTHREAD_UNLOCK);
}

void	x_lock_mutex_fork(t_fork *fork_n)
{
	int	ret;

	ret = pthread_mutex_lock(&fork_n->mtx_fork);
	if (ret != 0)
		set_err_num_fork(fork_n, ERR_PTHREAD_LOCK);
}

void	x_unlock_mutex_fork(t_fork *fork_n)
{
	int	ret;

	ret = pthread_mutex_unlock(&fork_n->mtx_fork);
	if (ret != 0)
		set_err_num_fork(fork_n, ERR_PTHREAD_UNLOCK);
}
