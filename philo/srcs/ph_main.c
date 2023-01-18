/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 13:56:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// NULL err値入れる
int	main(int argc, char **argv)
{
	t_philo_main	ph;

	if (!is_valid_values(&ph, argc, argv))
	{
		// printf("%s %d\n", ERR_STR, ph.error_num);
		printf("%s %zu\n", ERR_STR, ph.error_num);
		// printf("%s", ERR_STR);
		return (ERROR);
	}
	if (!build_struct_and_list(&ph, argc))
	{
		printf("%s", ERR_STR);
		return (ERROR);
	}
	init_mutex(&ph);
	if (ph.error_num > NUM_ERR_LOW)
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

// ./philo 4 310 200 100
// ./philo 5 800 200 200
// ./philo 5 800 200 200 7
// ./philo 4 410 200 200
