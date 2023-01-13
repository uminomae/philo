/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_parallel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 10:15:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//create thread num_people and monitor
void	run_parallel_process(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;
	// t_monitor_node	*end_monitor;

	num_people = ph->argv[1];
	// end_monitor = &ph->end_monitor;
	i = 0;
	get_start_time(ph);
	//監視者スレッド作成
	// create_and_run_pthread_monitor(end_monitor);
	while (i < num_people)
	{
		set_and_run_philo(ph, i);
		set_and_run_monitor(ph, i);
		// printf("run philo %zu\n", i);
		// printf("run monitor %zu\n", i);
		i++;
	}
	// join_pthread(ph);
	if (ph->died_struct.died_flag == true)
		put_stamp(get_time_milli_sec() - ph->start_time, ph->died_struct.died_id, DIED_STR);
}
