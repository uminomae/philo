/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/07 19:51:29 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示

static bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	// if (node_th->must_eat == TRUE && node_th->argv[5] == cnt)
	if (node_th->flag_must_eat == TRUE && node_th->times_must_eat >= cnt)
		return (TRUE);
	return (false);
}

void	change_state_philosopher(size_t i, t_pthread_node *node_th, long ms, size_t id)
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
	usleep(1000);
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
	t_fork_list		*list_fork;
	t_fork_node		*node_fork;

	node_th = (t_pthread_node *)ptr;
	list_fork = &node_th->ph->fork_list;
	id = node_th->id;
	cnt = 0;
	node_fork = get_fork_node(list_fork, id);
	while (1)
	{
		if (id == 1)
			run_case1();
		toggle_mutex_forks(LOCK, node_fork);
		// lock_mutex_monitor(&node_th->ph->monitor);

		printf("-------------%zu-----a\n", node_th->ph->monitor.ate_cnt);
		if (node_th->ph->monitor.ate_all == TRUE)
			break;

		change_state_philosopher(TAKEN_FORK, node_th, 0, id);
		change_state_philosopher(EATING, node_th, node_th->ph->argv[3], id);
		cnt++;

		if (is_required_times_ate(node_th, cnt))
		{
			node_th->ph->monitor.ate_cnt++;
			break;
		}
			if (node_th->ph->monitor.ate_cnt >= id)
			{
				node_th->ph->monitor.ate_all = TRUE;
				break;
			}
		
		// unlock_mutex_monitor(&node_th->ph->monitor);
		toggle_mutex_forks(UNLOCK, node_fork);

		change_state_philosopher(SLEEPING, node_th, node_th->ph->argv[4], id);
		change_state_philosopher(THINKING, node_th, 0, id);
	}
	destroy_mutex(node_th->ph);
	return (NULL);
}
