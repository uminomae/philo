/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/16 02:51:14 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 途中のエラーのfreeとdestroy
//timestampを戻す
//printfを別に任せる
int	main(int argc, char **argv)
{
	t_philo_main	ph;

	if (is_valid_values(&ph, argc, argv) == false)
	{
		printf("%s", ERR_STR);
		return (ERROR);
	}
	if (build_struct_and_list(&ph, argc) == 1)
		return (ERROR);
	init_mutex(&ph);
	// if (ph.error_num != 0)
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
// NG philo/に入れる
// 関数を使う順番に並べ替える
// 日本語のコメントはやめる
// num_peopleとnum_forkは厳密には分けた方が誤解が少ない。意味は通じるけども。
// taken a forkなので、それぞれ取った時に出力。
// timeのズレは無しでピッタリにする。
// NG case 4 410 200 200 死なないようにする。