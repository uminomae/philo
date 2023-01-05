/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 04:08:25 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	toggle_mutex_forks(t_pthread_node *node_th, t_list *list, size_t id, size_t flag);

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示
//if must_eat回食べたら ＞ exit(0)
void	*dining_philosophers(void *ptr)
{
	// t_philo	*node;
	t_pthread_node *node_th;
	size_t cnt;
	size_t id = 0;

	cnt = 0;
	node_th = (t_pthread_node *)ptr;
	// printf("run\n");
	while (1)
	{
		id = node_th->id;
		if (id == 1)
			x_usleep_ms(node_th->ph->sleep_seconds);
		toggle_mutex_forks(node_th, &node_th->ph->fork_list, id, 1);
		

		node_th->time_eating = get_time_milli_sec() - node_th->ph->start_time;
		x_usleep_ms(node_th->ph->argv[3]);
		printf("%ld ", node_th->time_eating);
		put_timestamp(node_th->ph, id, EATING);
		cnt++;
		toggle_mutex_forks(node_th, &node_th->ph->fork_list, id, 0);

		if (node_th->ph->must_eat == TRUE && node_th->ph->argv[5] == cnt){
			// puts("break");
			break;
		}
			
		node_th->time_sleeping = get_time_milli_sec() - node_th->ph->start_time;
		printf("%ld ", node_th->time_sleeping);
		put_timestamp(node_th->ph, id, SLEEPING);

		x_usleep_ms(node_th->ph->argv[4]);
		
		node_th->time_thinking = get_time_milli_sec() - node_th->ph->start_time;
		printf("%ld ", node_th->time_thinking);
		put_timestamp(node_th->ph, id, THINKING);


		
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

static void	toggle_mutex_forks(t_pthread_node *node_th, t_list *list, size_t id, size_t flag)
{
	t_fork_node	*node_fork;

	node_fork = get_fork_node(list, id);
	if (flag == TRUE)
	{
		lock_mutex(node_fork);

		node_th->time_fork = get_time_milli_sec() - node_th->ph->start_time;
		printf("%ld ", node_th->time_fork);
		put_timestamp(node_th->ph, id, TAKEN_FORK);

		lock_mutex(node_fork->next);
	}
	else if (flag == FALSE)
	{
		unlock_mutex(node_fork);
		unlock_mutex(node_fork->next);
	}
}
