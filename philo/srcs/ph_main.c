/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:34:08 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Sanitizeオプションつけた時に遅れる
//judge ate allのunlock。　x_lock で検索してその後のifをチェックする。
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

// 2800 3 is thinking
// 2800 3 has taken a fork
// 2800 1 has taken a fork
// 2800 1 is eating
// 2800 2 is sleeping
// 2802 0 is thinking
// 2802 4 is sleeping
// 2802 3 has taken a fork
// 2802 3 is eating
// 3000 1 is sleeping
// 3000 2 is thinking
// 3000 0 has taken a fork
// 3000 0 has taken a fork
// 3000 0 is eating
// 3002 3 is sleeping
// 3002 2 has taken a fork
// 3002 4 is thinking
// 3002 2 has taken a fork
// 3002 2 is eating
// 3200 1 is thinking
// 3200 4 has taken a fork
// 3200 1 has taken a fork
// 3200 4 has taken a fork
// 3200 4 is eating
//ここで全体が15遅れ。Sanitizeオプションつけた時に起きる遅れのような動き。
// 3415 3 is thinking
// 3415 1 has taken a fork
// 3415 3 has taken a fork
// 3415 1 is eating
//いつもは3800らへんで終わるはず。その手前のeatingで止まった。
//　で、494遅れてdiedが出た。
// 3909 0 is died

//whileの分だけラグが出る？