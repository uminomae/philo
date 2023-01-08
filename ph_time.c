/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 18:21:52 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	put_stamp(long time, size_t id, char *str)
{
	int	ret;

	ret = printf("%ld %zu %s\n", time, id, str);
	return (ret);
}

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

void	get_start_time(t_philo *ph)
{
	long	ret;

	ret = get_time_milli_sec();
	if (ret < 0)
		get_err_flag(ph);
	else
		ph->start_time = get_time_milli_sec();
}

int	x_usleep_ms(size_t ms)
{
	int	ret;

	ret = usleep(ms * 1000);
	return (ret);
}
