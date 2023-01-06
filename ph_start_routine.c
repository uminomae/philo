/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 13:51:36 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	toggle_mutex_forks(t_pthread_node *node_th, t_list *list_fork, size_t id, size_t flag);

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示
static bool	is_required_times_ate(t_pthread_node *node_th, size_t cnt)
{
	if (node_th->ph->must_eat == TRUE && node_th->ph->argv[5] == cnt)
		return (TRUE);
	return (false);
}

void	change_state_philosopher(t_pthread_node *node_th, long ms, size_t i,size_t id)
{
	node_th->time[i] = get_time_milli_sec() - node_th->ph->start_time;
	x_usleep_ms(ms);
	put_stamp(node_th->time[i], id, *node_th->status[i]);
}

void	*dining_philosophers(void *ptr)
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
		//dieの判定はこのあたり？
		change_state_philosopher(node_th, node_th->ph->argv[3], EATING, id);
		// run_eating(node_th, id);
		cnt++;
		toggle_mutex_forks(node_th, &node_th->ph->fork_list, id, FALSE);
		if (is_required_times_ate(node_th, cnt))
			break;
		// printf("-----------%s", *node_th->status[2]);
		change_state_philosopher(node_th, node_th->ph->argv[4], SLEEPING, id);
		// run_sleeping(node_th, id);
		change_state_philosopher(node_th, 0, THINKING, id);
		// run_thinking(node_th, id);
	}
	return (NULL);
}

static void	lock_mutex(t_fork_node *node)
{
	int	ret;

	ret = pthread_mutex_lock(&node->mutex);
	if (ret != 0)
		exit(1);
}

static void	unlock_mutex(t_fork_node *node)
{
	int	ret;

	ret = pthread_mutex_unlock(&node->mutex);
	if (ret != 0)
		exit(1);
}

static t_fork_node	*get_fork_node(t_list *list, size_t c)
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

//unlock_mutex(node_fork->next);を先にしている
void	toggle_mutex_forks(t_pthread_node *node_th, t_list *list_fork, size_t id, size_t flag)
{
	t_fork_node	*node_fork;

	node_fork = get_fork_node(list_fork, id);
	if (flag == TRUE)
	{
		lock_mutex(node_fork);
		change_state_philosopher(node_th, 0, TAKEN_FORK, id);
		// run_taken_fork(node_th, id);
		lock_mutex(node_fork->next);
	}
	else if (flag == FALSE)
	{
		unlock_mutex(node_fork->next);
		unlock_mutex(node_fork);
	}
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