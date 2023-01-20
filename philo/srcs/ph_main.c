/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:39:25 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ph	ph;

	if (!is_valid_values(&ph, argc, argv))
	{
		printf("%s", ERR_STR);
		return (ERROR);
	}
	if (!build_struct_and_list(&ph, argc))
	{
		printf("%s", ERR_STR);
		free_all(&ph);
		return (ERROR);
	}
	if (!run_parallel_process(&ph))
	{
		end_error(&ph);
		return (ERROR);
	}
	end_philo(&ph);
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