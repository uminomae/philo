/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 15:32:09 by uminomae         ###   ########.fr       */
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