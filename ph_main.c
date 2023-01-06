/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 04:09:52 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//死ぬと同時にmutexを防ぐ。まず死を確認する

int	main(int argc, char **argv)
{
	t_philo	ph;

	begin_philo(&ph, argc, argv);
	get_start_time(&ph);
	init_pthread_mutex(&ph);
	
	create_pthread(&ph);
	join_pthread(&ph);
	return (0);
}

	// printf("%ld\n",ph.start_time);
	// int i = 0;
	// while(i < 100){
	// 	usleep(200 * 1000);
	// 	size_t cur_time = get_time_milli_sec();
	// 	// printf("i = %d; get zu:\t%ld\n",i, cur_time);
	// 	printf("i = %d; diff zu:\t%ld\n",i, cur_time - ph.start_time);
	// 	i++;
	// }