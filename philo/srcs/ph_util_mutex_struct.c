/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 23:41:43 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	x_lock_mutex_ph(pthread_mutex_t *mutex_ph, t_ph *ph)
{
	if (pthread_mutex_lock(mutex_ph) != 0)
	{
		x_lock_mutex_ph(mutex_ph, ph);
		set_err_num_ph(ph, ERR_PTHREAD_LOCK);
		x_unlock_mutex_ph(mutex_ph, ph);
	}
}

void	x_unlock_mutex_ph(pthread_mutex_t *mutex_ph, t_ph *ph)
{
	if (pthread_mutex_unlock(mutex_ph) != 0)
	{
		x_lock_mutex_ph(mutex_ph, ph);
		set_err_num_ph(ph, ERR_PTHREAD_UNLOCK);
		x_unlock_mutex_ph(mutex_ph, ph);
	}
}

void	x_lock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mtx_st)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		x_lock_mutex_struct(&mutex_struct->mtx_ate_all, mutex_struct);
		set_err_num_mutex(mutex_struct, ERR_PTHREAD_LOCK);
		x_unlock_mutex_struct(&mutex_struct->mtx_ate_all, mutex_struct);
	}
}

void	x_unlock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mtx_st)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		x_lock_mutex_struct(&mutex_struct->mtx_ate_all, mutex_struct);
		set_err_num_mutex(mutex_struct, ERR_PTHREAD_UNLOCK);
		x_unlock_mutex_struct(&mutex_struct->mtx_ate_all, mutex_struct);
	}
}
