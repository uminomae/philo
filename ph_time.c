/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 11:12:33 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	put_timestamp(t_philo *ph, long time, size_t id, size_t i)
// {
// 	ph->put_type[i](id, time);
// 	// printf("%ld %zu%s\n", time, id, TAKEN_FORK_STR);
// }

void	put_stamp(long time, size_t id, char *str)
{
	printf("%ld %zu %s\n", time, id, str);
}

long	get_time_milli_sec(void)
{
	struct timeval	tp;
	long			milli_sec;

	gettimeofday(&tp, NULL);
	milli_sec = tp.tv_sec * 1000;
	milli_sec += tp.tv_usec /1000;
	return (milli_sec);
}

void	get_start_time(t_philo *ph)
{
	ph->start_time = get_time_milli_sec();
}

void	x_usleep_ms(size_t ms)
{
	int	ret;
	ret = usleep(ms * 1000);
	if (ret != 0)
		exit(1);
}