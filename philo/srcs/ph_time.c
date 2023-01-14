/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/14 23:00:41 by uminomae         ###   ########.fr       */
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

int	wait_action_usleep_ms(long start, size_t wait_ms)
{
	int		ret;
	long	total;
	long	wait_must;

	ret = 0;
	total = wait_ms + start;
	while(total >= get_time_milli_sec())
	{
		wait_must = total - get_time_milli_sec();
		if (wait_must > 10)
		{
			ret = usleep(1000);
			if (ret < 0)
				return(ret);
		}
	}
	return (ret);
}

// int	usleep_ms(size_t ms)
// {
// 	int	ret;

// 	ret = usleep(ms * 1000);
// 	return (ret);
// }
