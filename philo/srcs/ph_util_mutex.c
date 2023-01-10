/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:17:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/10 17:02:40 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	x_lock_mutex(pthread_mutex_t *mutex, t_eat_monitor *eat_monitor)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret != 0)
		get_err_flag_eat_monitor(eat_monitor);
}

void	x_unlock_mutex(pthread_mutex_t *mutex, t_eat_monitor *eat_monitor)
{
	int	ret;

	ret = pthread_mutex_unlock(mutex);
	if (ret != 0)
		get_err_flag_eat_monitor(eat_monitor);
}
