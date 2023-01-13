/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 10:44:07 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO エラー処理
void	x_lock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mutex_struct)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		x_lock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
		get_err_num(mutex_struct, ERR_PTHREAD_LOCK);
		x_unlock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
	}
}

void	x_unlock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mutex_struct)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		x_lock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
		get_err_num(mutex_struct, ERR_PTHREAD_UNLOCK);
		x_unlock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
	}
}

void	x_lock_mutex_philo(t_philo_node *node_philo)
{
	int	ret;

	ret = pthread_mutex_lock(&node_philo->mutex_philo);
	if (ret != 0)
	{
		x_lock_mutex_philo(node_philo);
		get_err_num_ph(node_philo->ph, ERR_PTHREAD_LOCK);
		x_unlock_mutex_philo(node_philo);
	}
}

void	x_unlock_mutex_philo(t_philo_node *node_philo)
{
	int	ret;

	ret = pthread_mutex_unlock(&node_philo->mutex_philo);
	if (ret != 0)
	{
		x_lock_mutex_philo(node_philo);
		get_err_num_ph(node_philo->ph, ERR_PTHREAD_UNLOCK);
		x_unlock_mutex_philo(node_philo);
	}
}





void	x_lock_mutex(pthread_mutex_t *mutex, t_monitor_node *end_monitor)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret != 0)
		get_err_flag_end_monitor(end_monitor);
}

void	x_unlock_mutex(pthread_mutex_t *mutex, t_monitor_node *end_monitor)
{
	int	ret;

	ret = pthread_mutex_unlock(mutex);
	if (ret != 0)
		get_err_flag_end_monitor(end_monitor);
}

void	x_lock_mutex_fork(t_fork_node *node_fork)
{
	int	ret;

	ret = pthread_mutex_lock(&node_fork->mutex_fork);
	if (ret != 0)
		get_err_flag_node_fork(node_fork);
}

void	x_unlock_mutex_fork(t_fork_node *node_fork)
{
	// int	ret;

	// ret = pthread_mutex_unlock(&node_fork->mutex_fork);
	pthread_mutex_unlock(&node_fork->mutex_fork);
	// if (ret != 0)
	// 	get_err_flag_node_fork(node_fork);
}
