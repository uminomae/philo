/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/27 14:25:57 by uminomae         ###   ########.fr       */
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

//[global]
// serch "extern"
//[check leak]
// system("leaks -q philo");
//[test case]
//	make sani_thread
// ./philo 1 800 200 200
// ./philo 5 800 200 200
// ./philo 5 800 200 200 7
// ./philo 4 310 200 100
// ./philo 4 410 200 200
//
//other
// ./philo 5 1410 200 500
// ./philo 5 510 200 100
// 
//grep died
// ./philo 200 2000 1000 1000 > out1; 
//id=`< out1 grep died | awk '{print $2}'`; 
//str=" ${id} is "; < out1 grep "$str";
//gerp is eating
// ./philo 5 800 200 200 7 > out2; echo "`< out2 grep " is eating"`";
//must_eat
// ANS0=`< out2 cat | grep " 0 is eating" | wc -l`;
// ANS1=`< out2 cat | grep " 1 is eating" | wc -l`;
// ANS2=`< out2 cat | grep " 2 is eating" | wc -l`;
// ANS3=`< out2 cat | grep " 3 is eating" | wc -l`;
// ANS4=`< out2 cat | grep " 4 is eating" | wc -l`;
// if [ ${ANS0} -ge 7 ] && [ ${ANS1} -ge 7 ] && 
//[ ${ANS2} -ge 7 ] && [ ${ANS3} -ge 7 ] && [ ${ANS4} -ge 7 ]; then
// 	echo "--------OK--------";
// else
// 	echo "--------NG--------";
// fi;
//
//[debug]
// printf("%sERROR NUM=%zu\n", ERR_STR, ph.err_num);