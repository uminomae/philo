/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 11:04:47 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	toggle_mutex_forks(t_pthread_node *node_th, t_list *list, size_t id, size_t flag);

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示
//if must_eat回食べたら ＞ break
void	*dining_philosophers(void *ptr)
{
	t_pthread_node *node_th;
	size_t cnt;
	size_t id = 0;

	cnt = 0;
	node_th = (t_pthread_node *)ptr;
	while (1)
	{
		id = node_th->id;
		if (id == 1)
			usleep(50);
			// x_usleep_ms(node_th->ph->sleep_seconds);
		//taken_fork
		toggle_mutex_forks(node_th, &node_th->ph->fork_list, id, TRUE);
		//eating
		node_th->time_eating = get_time_milli_sec() - node_th->ph->start_time;
		x_usleep_ms(node_th->ph->argv[3]);
		put_stamp(node_th->time_eating, id, EATING_STR);
		// put_timestamp(node_th->ph, node_th->time_eating, id, EATING);
		cnt++;
		toggle_mutex_forks(node_th, &node_th->ph->fork_list, id, FALSE);
		if (node_th->ph->must_eat == TRUE && node_th->ph->argv[5] == cnt){
			break;
		}
		//sleeping
		node_th->time_sleeping = get_time_milli_sec() - node_th->ph->start_time;
		x_usleep_ms(node_th->ph->argv[4]);
		put_timestamp(node_th->ph, node_th->time_sleeping, id, SLEEPING);
		//thinking
		node_th->time_thinking = get_time_milli_sec() - node_th->ph->start_time;
		put_timestamp(node_th->ph, node_th->time_thinking, id, THINKING);
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
static void	toggle_mutex_forks(t_pthread_node *node_th, t_list *list, size_t id, size_t flag)
{
	t_fork_node	*node_fork;

	node_fork = get_fork_node(list, id);
	if (flag == TRUE)
	{
		lock_mutex(node_fork);

		node_th->time_fork = get_time_milli_sec() - node_th->ph->start_time;
		put_timestamp(node_th->ph, node_th->time_fork, id, TAKEN_FORK);

		lock_mutex(node_fork->next);
	}
	else if (flag == FALSE)
	{
		unlock_mutex(node_fork->next);
		unlock_mutex(node_fork);
	}
}
