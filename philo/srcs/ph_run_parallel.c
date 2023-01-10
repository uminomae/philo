/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_parallel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 00:04:51 by uminomae         ###   ########.fr       */
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

static void	join_pthread(t_philo *ph)
{
	size_t			i;
	size_t			num_people;
	int				ret;
	t_pthread_node	*node_th;

	num_people = ph->argv[1];
	ret = pthread_join(ph->end_monitor.monitor_th, NULL);
	i = 0;
	while (i < num_people)
	{
		node_th = get_pthread_node(&ph->thread_list, i);
		// x_lock_mutex_th(node_th);
		ret = pthread_join(node_th->thread, NULL);
		if (ret != 0)
			get_err_flag_node_th(node_th);
		// x_unlock_mutex_th(node_th);
		i++;
	}
}

void	end_flag_th(t_philo *ph)
{
	size_t			i;
	size_t			num_people;
	t_pthread_node	*node_th;

	num_people = ph->argv[1];
	i = 0;
	while (i < num_people)
	{
		node_th = get_pthread_node(&ph->thread_list, i);
		x_lock_mutex_th(node_th);
		node_th->flag_end = true;
		x_unlock_mutex_th(node_th);
		i++;
	}
}

bool rutine_judge_end_in_thread(t_pthread_monitor *end_monitor)
{
	pthread_mutex_t	*mutex_eat;

	mutex_eat = &end_monitor->eat_monitor.mutex_eat;
	if (is_flag_died(end_monitor))
		return (true);
	x_lock_mutex(mutex_eat, end_monitor);
	if (judge_ate_all(end_monitor, end_monitor->ph->argv[1]))
		return (true);
	x_unlock_mutex(mutex_eat, end_monitor);
	return (false);
}

void	*end_monitor_in_thread(void *ptr)
{
	t_pthread_monitor	*end_monitor;

	end_monitor = (t_pthread_monitor *)ptr;
	while (1)
	{
		if (rutine_judge_end_in_thread(end_monitor))
			break ;
	}
	end_flag_th(end_monitor->ph);
	// join_pthread(end_monitor->ph);
	return (ptr);
}

static void	create_and_run_pthread_philo(t_pthread_node *node_th)
{
	int	ret;

	ret = pthread_create(&node_th->thread, NULL, \
		dining_philosophers_in_thread, node_th);
	if (ret != 0)
		get_err_flag_node_th(node_th);
}

static void	create_and_run_pthread_monitor(t_pthread_monitor *end_monitor)
{
	int	ret;

	ret = pthread_create(&end_monitor->monitor_th, NULL, end_monitor_in_thread, end_monitor);
	if (ret != 0)
		get_err_flag_eat_monitor(&end_monitor->eat_monitor);
	// join_pthread(end_monitor->ph);
	// join_pthread(end_monitor->ph);
}

void	run_parallel_process(t_philo *ph)
{
	size_t			i;
	t_pthread_node	*node_th;
	size_t			num_people;
	t_pthread_monitor	*end_monitor;

	num_people = ph->argv[1];
	end_monitor = &ph->end_monitor;
	i = 0;
	get_start_time(ph);
	create_and_run_pthread_monitor(end_monitor);
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
	if (ph->end_monitor.die_monitor.flag_died == true)
		put_state(DIED, node_th, 0, node_th->id);
}
