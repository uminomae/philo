/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 15:55:00 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// errnoで格納　size_t
// 監視役th
// detachとwhile(1)で終了
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
// NG philo/に入れる
// 関数を使う順番に並べ替える
// 日本語のコメントはやめる
// num_peopleとnum_forkは厳密には分けた方が誤解が少ない。意味は通じるけども。
// taken a forkなので、それぞれ取った時に出力。
// timeのズレは無しでピッタリにする。
// NG case 4 410 200 200 死なないようにする。