/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 18:01:46 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO 死ぬと同時にmutexを防ぐ。まず死を確認する
int	main(int argc, char **argv)
{
	t_philo	ph;

	if (is_valid_values(&ph, argc, argv) == false)
	{
		printf("%s", ERR_STR);
		return (ERROR);
	}
	if (build_struct_and_list(&ph, argc) == 1)
		return (ERROR);
	init_mutex(&ph);
	if (ph.flag_err == true)
	{
		end_error(&ph);
		return (ERROR);
	}
	run_parallel_process(&ph);
	if (is_error(&ph) == true)
	{
		end_error(&ph);
		return (ERROR);
	}
	end_philo(&ph);
	return (SUCCESS);
}
	// system("leaks -q philo");
