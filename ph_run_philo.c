/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/07 20:41:50 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示

static bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == TRUE && node_th->times_must_eat == cnt)
		return (TRUE);
	return (false);
}

void	change_state_and_putstamp(size_t i, t_pthread_node *node_th, long ms, size_t id)
{
	long	ret;

	ret = get_time_milli_sec();
	if (ret < 0)
		node_th->flag_err = TRUE;
	node_th->time[i] = ret - node_th->ph->start_time;
	if (x_usleep_ms(ms) < 0)
		node_th->flag_err = TRUE;
	if (put_stamp(node_th->time[i], id, *node_th->status[i]) < 0)
		node_th->flag_err = TRUE;
}

void	run_case1()
{
	//gettimeofday入れる
	usleep(100);
	// usleep(40);←lower 後で考える。
	// if (x_usleep_ms(node_th->ph->sleep_seconds / 2) < 0)
	// 	node_th->flag_err = TRUE;
}

// err
// モニタのスレッドを立てる。メモリ領域に同時に書き込みがある可能性。データレースでググる
//　共有メモリの最小化、先行順序をつける。で対応する。
void	*dining_philosophers_in_thread(void *ptr)
{
	t_pthread_node	*node_th;
	size_t			cnt;
	size_t			id;
	t_fork_node		*node_fork;

	node_th = (t_pthread_node *)ptr;
	id = node_th->id;
	cnt = 0;
	node_fork = get_fork_node(&node_th->ph->fork_list, id);
	while (1)
	{
		if (id == 1)
			run_case1();
		toggle_mutex(LOCK, &node_th->ph->monitor, node_fork);
		//切り分ける----------------//
		if (node_th->ph->monitor.ate_all == TRUE)
		{
			toggle_mutex(UNLOCK, &node_th->ph->monitor, node_fork);
			break;
		}
		//----------------//
		change_state_and_putstamp(TAKEN_FORK, node_th, 0, id);
		change_state_and_putstamp(EATING, node_th, node_th->ph->argv[3], id);
		cnt++;
		if (is_required_times_ate(node_th, cnt))
			node_th->ph->monitor.ate_cnt++;
		//切り分ける
		if (node_th->ph->monitor.ate_cnt == node_th->ph->argv[1])
		{
			node_th->ph->monitor.ate_all = TRUE;
			toggle_mutex(UNLOCK, &node_th->ph->monitor, node_fork);
			break;
		}
		//----------------//
		toggle_mutex(UNLOCK, &node_th->ph->monitor, node_fork);
		change_state_and_putstamp(SLEEPING, node_th, node_th->ph->argv[4], id);
		change_state_and_putstamp(THINKING, node_th, 0, id);
	}
	return (NULL);
}
