/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_philo_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 11:50:51 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示
//TODO 優先順位 tailだったら条件で。
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
	long	time_current;

	time_current = get_time_milli_sec();
	if (time_current < 0)
		node_th->flag_err = TRUE;
	node_th->time[i] = time_current - node_th->start_time;
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
	// usleep(100);
	// usleep(40);←lower 後で考える。
	// if (x_usleep_ms(node_th->ph->sleep_seconds / 2) < 0)
	// 	node_th->flag_err = TRUE;
}

// err
// モニタのスレッドを立てる?
// longにargvを修正
void	*dining_philosophers_in_thread(void *ptr)
{
	t_pthread_node	*node_th;
	t_fork_node		*node_fork;
	long			time_eat;
	long			time_sleep;
	// int				ret;
	long	time_current;

	node_th = (t_pthread_node *)ptr;
	time_eat = node_th->ph->argv[3];
	time_sleep = node_th->ph->argv[4];
	node_fork = get_fork_node(&node_th->ph->fork_list, node_th->id);
	while (1)
	{
		time_current = get_time_milli_sec();
		if (time_current < 0)
			node_th->flag_err = TRUE;
		if (node_th->id == 1)
			run_case1person();
		if (time_current - (node_th->start_time + node_th->time[EATING]) >= (long)node_th->ph->argv[2])
		{
			x_pthread_mutex_lock(&node_th->ph->die_monitor.mutex, &node_th->ph->monitor);
			node_th->ph->die_monitor.flag_died = true;
			x_pthread_mutex_unlock(&node_th->ph->die_monitor.mutex, &node_th->ph->monitor);
			break;
		}
		x_pthread_mutex_lock(&node_th->ph->die_monitor.mutex, &node_th->ph->monitor);
		if (node_th->ph->die_monitor.flag_died == true)
			break ;
		x_pthread_mutex_unlock(&node_th->ph->die_monitor.mutex, &node_th->ph->monitor);
		//TODO ret消す
		if (lock_mutex_and_eat_starting(node_th, node_fork, node_th->id, time_eat) > 0);
		// ret = lock_mutex_and_eat_starting(node_th, node_fork, node_th->id, time_eat);
		// if (ret > 0)
			break ;
		change_state_and_putstamp(SLEEPING, node_th, time_sleep, node_th->id);
		change_state_and_putstamp(THINKING, node_th, 0, node_th->id);
	}
	return (NULL);
}
