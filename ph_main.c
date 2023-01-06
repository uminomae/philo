/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 22:53:11 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO 死ぬと同時にmutexを防ぐ。まず死を確認する
int	main(int argc, char **argv)
{
	t_philo	ph;

	begin_philo(&ph, argc, argv);
	if (is_error(&ph) == TRUE)
		return (0);
	init_mutex(&ph);
	run_parallel_process(&ph);
	end_philo(&ph);
	// system("leaks -q philo");
	return (0);
}
