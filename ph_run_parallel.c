/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_parallel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 03:21:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_pthread_node	*get_pthread_node(t_pthread_list *list_th, size_t id)
{
	size_t			i;
	t_pthread_node	*node_th;

	node_th = list_th->head;
	i = 0;
	while (i < id)
	{
		node_th = node_th->next;
		i++;
	}
	return (node_th);
}

//TODO 関数が失敗した場合　manで確認する
static void	join_pthread(t_philo *ph)
{
	size_t			i;
	size_t			num_people;
	int				ret;
	t_pthread_node	*node_th;

	num_people = ph->argv[1];
	i = 0;
	while (i < num_people)
	{
		node_th = get_pthread_node(&ph->thread_list, i);
		ret = pthread_join(node_th->thread, NULL);
		if (ret != 0)
			get_err_flag_node_th(node_th);
		i++;
	}
}

static void create_and_run_pthread_philo(t_pthread_node *node_th)
{
	int	ret;

	
	ret = pthread_create(&node_th->thread, NULL, dining_philosophers_in_thread, node_th);
	if (ret != 0)
		get_err_flag_node_th(node_th);
}

void	run_parallel_process(t_philo *ph)
{
	size_t			i;
	t_pthread_node	*node_th;
	size_t			num_people;

	num_people = ph->argv[1];
	i = 0;
	get_start_time(ph);
	while (i < num_people)
	{
		node_th = get_pthread_node(&ph->thread_list, i);
		node_th->id = i;
		node_th->start_time = ph->start_time;
		node_th->flag_must_eat = ph->flag_must_eat;
		node_th->times_must_eat = ph->argv[5];
		create_and_run_pthread_philo(node_th);
		i++;
	}
	join_pthread(ph);
	pthread_mutex_lock(&ph->die_monitor.mutex);
	if (ph->die_monitor.flag_died == true)
		change_state_and_putstamp(DIED, node_th, 0, node_th->id);
	pthread_mutex_unlock(&ph->die_monitor.mutex);
}
