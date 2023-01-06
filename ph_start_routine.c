/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 14:24:54 by uminomae         ###   ########.fr       */
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
	t_pthread_node	*node_th;
	size_t			cnt;
	size_t			id;
	t_fork_list			*list_fork;

	node_th = (t_pthread_node *)ptr;
	list_fork = &node_th->ph->fork_list;
	id = node_th->id;
	cnt = 0;
	while (1)
	{
		if (id == 1)
			x_usleep_ms(node_th->ph->sleep_seconds / 2);
			// usleep(40);←lower 後で考える。
		toggle_mutex_forks(TRUE, node_th, list_fork, id);
		change_state_philosopher(EATING, node_th, node_th->ph->argv[3], id);
		cnt++;
		toggle_mutex_forks(FALSE, node_th, list_fork, id);
		if (is_required_times_ate(node_th, cnt))
			break;
		change_state_philosopher(SLEEPING, node_th, node_th->ph->argv[4], id);
		change_state_philosopher(THINKING, node_th, 0, id);
	}
	return (NULL);
}
