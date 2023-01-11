/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 19:08:25 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO エラー処理
void	x_lock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mutex_struct)
{
	if (pthread_mutex_lock(mutex) != 0)
		get_err_num(mutex_struct, ERR_PTHREAD_LOCK);
}

void	x_unlock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mutex_struct)
{
	pthread_mutex_unlock(mutex);
	if (pthread_mutex_unlock(mutex) != 0)
		get_err_num(mutex_struct, ERR_PTHREAD_UNLOCK);
}


void	x_lock_mutex(pthread_mutex_t *mutex, t_pthread_monitor_node *end_monitor)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret != 0)
		get_err_flag_end_monitor(end_monitor);
}

void	x_unlock_mutex(pthread_mutex_t *mutex, t_pthread_monitor_node *end_monitor)
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
	int	ret;

	ret = pthread_mutex_unlock(&node_fork->mutex_fork);
	if (ret != 0)
		get_err_flag_node_fork(node_fork);
}

void	x_lock_mutex_philo(t_philo_node *node_th)
{
	int	ret;

	ret = pthread_mutex_lock(&node_th->mutex_philo);
	if (ret != 0)
		get_err_flag_node_th(node_th);
}

void	x_unlock_mutex_philo(t_philo_node *node_th)
{
	int	ret;

	ret = pthread_mutex_unlock(&node_th->mutex_philo);
	if (ret != 0)
		get_err_flag_node_th(node_th);
}