/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 15:54:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_struct_philo(t_philo *ph)
{
	memset(ph, 0, sizeof(t_philo));
}

// TODO 人数1名の時の処理
void	begin_philo(t_philo *ph, int argc, char **argv)
{
	check_valid_values(argc, argv);
	init_struct_philo(ph);
	build_struct_and_list(ph, argc, argv);
	// if (ph->argv[1] == 1)
	// {
	// 	put_stamp(time, 1, DIED_STR);
	// 	exit(0);
	// }
}
