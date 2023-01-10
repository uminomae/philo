/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/10 23:58:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	x_lock_mutex(pthread_mutex_t *mutex, t_pthread_monitor *end_monitor)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret != 0)
		get_err_flag_end_monitor(end_monitor);
}

void	x_unlock_mutex(pthread_mutex_t *mutex, t_pthread_monitor *end_monitor)
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

void	x_lock_mutex_th(t_pthread_node *node_th)
{
	int	ret;

	ret = pthread_mutex_lock(&node_th->mutex_th);
	if (ret != 0)
		get_err_flag_node_th(node_th);
}

void	x_unlock_mutex_th(t_pthread_node *node_th)
{
	int	ret;

	ret = pthread_mutex_unlock(&node_th->mutex_th);
	if (ret != 0)
		get_err_flag_node_th(node_th);
}