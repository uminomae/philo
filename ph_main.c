/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/04 18:51:03 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//死ぬと同時にmutexを防ぐ。まず死を確認する
size_t get_time_milli_sec(void)
{
	struct timeval	tp;
	size_t			milli_sec;

	gettimeofday(&tp, NULL);
	milli_sec = tp.tv_sec * 1000;
	milli_sec += tp.tv_usec /1000;
	return (milli_sec);
}

int	main(int argc, char **argv)
{
	t_philo	ph;

	begin_philo(&ph, argc, argv);

	ph.start_time = get_time_milli_sec();
	printf("%ld\n",ph.start_time);
	int i = 0;
	while(i < 100){
		usleep(200 * 1000);
		size_t cur_time = get_time_milli_sec();
		// printf("i = %d; get zu:\t%ld\n",i, cur_time);
		printf("i = %d; diff zu:\t%ld\n",i, cur_time - ph.start_time);
		i++;
	}
	
	init_pthread_mutex(&ph);
	create_pthread(&ph);
	join_pthread(&ph);
	put_timestamp(&ph, 1, 0);
	return (0);
}
