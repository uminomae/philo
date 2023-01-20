/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:37:23 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	x_lock_mutex_philo(t_philo *node_philo)
{
	int	ret;

	ret = pthread_mutex_lock(&node_philo->mutex_philo);
	if (ret != 0)
		get_err_num_ph(node_philo->ph, ERR_PTHREAD_LOCK);
}

void	x_unlock_mutex_philo(t_philo *node_philo)
{
	int	ret;

	ret = pthread_mutex_unlock(&node_philo->mutex_philo);
	if (ret != 0)
		get_err_num_ph(node_philo->ph, ERR_PTHREAD_UNLOCK);
}

void	x_lock_mutex_fork(t_fork *node_fork)
{
	int	ret;

	ret = pthread_mutex_lock(&node_fork->mutex_fork);
	if (ret != 0)
		get_err_num_fork(node_fork, ERR_PTHREAD_LOCK);
}

void	x_unlock_mutex_fork(t_fork *node_fork)
{
	int	ret;

	ret = pthread_mutex_unlock(&node_fork->mutex_fork);
	if (ret != 0)
		get_err_num_fork(node_fork, ERR_PTHREAD_UNLOCK);
}
