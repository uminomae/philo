/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 16:28:00 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// NULL err値入れる
int	main(int argc, char **argv)
{
	t_philo_main	ph;

	if (!is_valid_values(&ph, argc, argv))
	{
		printf("%sERROR NUM=%zu\n", ERR_STR, ph.error_num);
		// printf("%s", ERR_STR);
		return (ERROR);
	}
	if (!build_struct_and_list(&ph, argc))
	{
		printf("%sERROR NUM=%zu\n", ERR_STR, ph.error_num);
		// printf("%s", ERR_STR);
		return (ERROR);
	}
	if (!init_mutex(&ph))
	{
		printf("%sERROR NUM=%zu\n", ERR_STR, ph.error_num);
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
	system("leaks -q philo");
	return (SUCCESS);
}

//[check leak]
// system("leaks -q philo");

//[test case]
//	make sani_thread
// ./philo 4 310 200 100
// ./philo 5 800 200 200
// ./philo 5 800 200 200 7
// ./philo 4 410 200 200

//[debug]
// printf("%sERROR NUM=%zu\n", ERR_STR, ph.error_num);