/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 01:45:06 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO 死ぬと同時にmutexを防ぐ。まず死を確認する
int	main(int argc, char **argv)
{
	t_philo	ph;

	begin_philo(&ph, argc, argv);
	if (is_error(&ph) == FALSE)
		run_parallel_process(&ph);
	if (is_error(&ph) == TRUE)
	{
		end_error(&ph);
		return (ERROR);
	}
	end_philo(&ph);
	// system("leaks -q philo");
	return (SUCCESS);
}
