/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 21:32:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_milli_sec(void)
{
	struct timeval	tp;
	long			milli_sec;
	int				ret;

	ret = gettimeofday(&tp, NULL);
	if (ret < 0)
		return (-1);
	milli_sec = tp.tv_sec * 1000;
	milli_sec += tp.tv_usec / 1000;
	return (milli_sec);
}

// long	get_time_passed(t_philo_main *ph)
// {
// 	long	ret;

// 	ret = get_time_milli_sec();
// 	if (ret < 0)
// 		get_err_num_ph(ph, ERR_GETTEIMEOFDAY);
// 	else
// 		ph->passed_time = ret;
// 	return (ret);
// }

int	usleep_ms(size_t ms)
{
	int	ret;

	ret = usleep(ms * 1000);
	return (ret);
}
