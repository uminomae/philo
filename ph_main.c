/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 15:26:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//死ぬと同時にmutexを防ぐ。まず死を確認する


int	main(int argc, char **argv)
{
	t_philo	ph;

	begin_philo(&ph, argc, argv);
	get_start_time(&ph);
	init_mutex(&ph);
	run_parallel_process(&ph);
	end_philo(&ph);
	// system("leaks -q philo");
	return (0);
}
