/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 04:15:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	x_lock_mutex(pthread_mutex_t *mutex, t_monitor *monitor)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret != 0)
		get_err_flag_monitor(monitor);
}

void	x_unlock_mutex(pthread_mutex_t *mutex, t_monitor *monitor)
{
	int	ret;

	ret = pthread_mutex_unlock(mutex);
	if (ret != 0)
		get_err_flag_monitor(monitor);
}
