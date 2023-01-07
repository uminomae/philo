/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 01:14:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示

static t_fork_node	*get_fork_node(t_fork_list *list, size_t c)
{
	size_t	i;
	t_fork_node	*node;

	node = list->head;
	i = 0;
	while (i < c)
	{
		node = node->next;
		i++;
	}
	return (node);
}

void	change_state_and_putstamp(size_t i, t_pthread_node *node_th, long ms, size_t id)
{
	long	ret;

	ret = get_time_milli_sec();
	if (ret < 0)
		node_th->flag_err = TRUE;
	node_th->time[i] = ret - node_th->ph->start_time;
	if (ms != 0)
	{
		if (x_usleep_ms(ms) < 0)
			node_th->flag_err = TRUE;
	}
	if (put_stamp(node_th->time[i], id, *node_th->status[i]) < 0)
		node_th->flag_err = TRUE;
}

void	run_case1person()
{
	//gettimeofday入れる
	usleep(100);
	// usleep(40);←lower 後で考える。
	// if (x_usleep_ms(node_th->ph->sleep_seconds / 2) < 0)
	// 	node_th->flag_err = TRUE;
}

// err
// モニタのスレッドを立てる。メモリ領域に同時に書き込みがある可能性。データレースでググる
void	*dining_philosophers_in_thread(void *ptr)
{
	t_pthread_node	*node_th;
	// size_t			cnt;
	size_t			id;
	t_fork_node		*node_fork;
	int				ret;

	node_th = (t_pthread_node *)ptr;
	id = node_th->id;
	node_fork = get_fork_node(&node_th->ph->fork_list, id);
	// node_th->cnt = 0;
	while (1)
	{
		if (id == 1)
			run_case1person();
		ret = lock_mutex_and_eat_starting(node_th, node_fork, id);
		if(ret == 1)
			break;
		change_state_and_putstamp(SLEEPING, node_th, node_th->ph->argv[4], id);
		change_state_and_putstamp(THINKING, node_th, 0, id);
	}
	return (NULL);
}
