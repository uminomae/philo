/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 14:05:38 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示

static bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->ph->must_eat == TRUE && node_th->ph->argv[5] == cnt)
		return (TRUE);
	return (false);
}

void	change_state_philosopher(size_t i, t_pthread_node *node_th, long ms, size_t id)
{
	node_th->time[i] = get_time_milli_sec() - node_th->ph->start_time;
	x_usleep_ms(ms);
	put_stamp(node_th->time[i], id, *node_th->status[i]);
}

void	*dining_philosophers_in_thread(void *ptr)
{
	t_pthread_node *node_th;
	size_t cnt;
	size_t id;

	cnt = 0;
	id = 0;
	node_th = (t_pthread_node *)ptr;
	while (1)
	{
		id = node_th->id;
		if (id == 1)
			// usleep(40);←lower 後で考える。
			x_usleep_ms(node_th->ph->sleep_seconds / 2);
		toggle_mutex_forks(node_th, &node_th->ph->fork_list, id, TRUE);
		change_state_philosopher(EATING, node_th, node_th->ph->argv[3], id);
		cnt++;
		toggle_mutex_forks(node_th, &node_th->ph->fork_list, id, FALSE);
		if (is_required_times_ate(node_th, cnt))
			break;
		change_state_philosopher(SLEEPING, node_th, node_th->ph->argv[4], id);
		change_state_philosopher(THINKING, node_th, 0, id);
	}
	return (NULL);
}

// static	void run_taken_fork(t_pthread_node *node_th, size_t id)
// {
// 	node_th->time_fork = get_time_milli_sec() - node_th->ph->start_time;
// 	x_usleep_ms(0);
// 	put_stamp(node_th->time_fork, id, TAKEN_FORK_STR);
// }

// static void	run_eating(t_pthread_node *node_th, size_t id)
// {
// 	node_th->time_eating = get_time_milli_sec() - node_th->ph->start_time;
// 	x_usleep_ms(node_th->ph->argv[3]);
// 	put_stamp(node_th->time_eating, id, EATING_STR);
// }

// static void	run_sleeping(t_pthread_node *node_th, size_t id)
// {
// 	node_th->time_sleeping = get_time_milli_sec() - node_th->ph->start_time;
// 	x_usleep_ms(node_th->ph->argv[4]);
// 	put_stamp(node_th->time_sleeping, id, SLEEPING_STR);
// }

// static void	run_thinking(t_pthread_node *node_th, size_t id)
// {
// 	node_th->time_thinking = get_time_milli_sec() - node_th->ph->start_time;
// 	x_usleep_ms(0);
// 	put_stamp(node_th->time_thinking, id, THINKING_STR);
// }