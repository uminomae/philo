/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_parallel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 20:17:33 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	join_pthread(t_philo_main *ph)
// {
// 	size_t			i;
// 	size_t			num_people;
// 	int				ret;
// 	t_philo_node	*node_th;

// 	num_people = ph->argv[1];
// 	ret = pthread_join(ph->end_monitor.monitor_th, NULL);
// 	i = 0;
// 	while (i < num_people)
// 	{
// 		node_th = get_philo_node(&ph->philo_list, i);
// 		// x_lock_mutex_philo(node_th);
// 		ret = pthread_join(node_th->thread, NULL);
// 		if (ret != 0)
// 			get_err_flag_node_th(node_th);
// 		// x_unlock_mutex_philo(node_th);
// 		i++;
// 	}
// }


void	put_state(size_t i, t_philo_node *node_philo, long ms, size_t id)
{
	long	time_current;

	time_current = get_time_milli_sec();
	if (time_current < 0)
		node_philo->flag_err = true;
	node_philo->time[i] = time_current - node_philo->start_time;
	if (put_stamp(node_philo->time[i], id, *node_philo->status[i]) < 0)
		node_philo->flag_err = true;
	if (ms != 0)
	{
		if (usleep_ms(ms) < 0)
			node_philo->flag_err = true;
	}
}

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
		i++;
	}
	// join_pthread(ph);
	if (ph->died_struct.died_flag == true)
		put_stamp(get_time_milli_sec() - ph->start_time, ph->died_struct.died_id, DIED_STR);
}
