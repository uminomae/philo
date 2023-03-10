/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_x_stdlib.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 11:58:17 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	x_usleep_millisec(t_ph *ph, long time_ms)
{
	long	ret;

	ret = usleep(time_ms * 1000);
	if (ret == -1)
	{
		set_err_num_ph(ph, ERR_USLEEP);
		return (false);
	}
	return (true);
}

bool	x_usleep_microsec(t_ph *ph, long time_microsec)
{
	long	ret;

	ret = usleep(time_microsec);
	if (ret == -1)
	{
		set_err_num_ph(ph, ERR_USLEEP);
		return (false);
	}
	return (true);
}

bool	x_pthread_create(t_ph *ph, pthread_t *t, \
				void *(*f)(void *), void *p)
{
	int	ret;

	ret = pthread_create(t, NULL, f, p);
	if (ret != 0)
	{
		set_err_num_ph(ph, ERR_PTHREAD_CREATE);
		return (false);
	}
	return (true);
}

bool	x_pthread_detach(t_ph *ph, pthread_t *thread)
{
	int	ret;

	ret = pthread_detach(*thread);
	if (ret != 0)
	{
		set_err_num_ph(ph, ERR_PTHREAD_DETACH);
		return (false);
	}
	return (true);
}
