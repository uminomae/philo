/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_parallel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 19:08:25 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo_node	*get_philo_node(t_philo_list *list_th, size_t id)
{
	size_t			i;
	t_philo_node	*node_th;

	node_th = list_th->head;
	i = 0;
	while (i < id)
	{
		node_th = node_th->next;
		i++;
	}
	return (node_th);
}

static void	join_pthread(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;
	int				ret;
	t_philo_node	*node_th;

	num_people = ph->argv[1];
	ret = pthread_join(ph->end_monitor.monitor_th, NULL);
	i = 0;
	while (i < num_people)
	{
		node_th = get_philo_node(&ph->thread_list, i);
		// x_lock_mutex_philo(node_th);
		ret = pthread_join(node_th->thread, NULL);
		if (ret != 0)
			get_err_flag_node_th(node_th);
		// x_unlock_mutex_philo(node_th);
		i++;
	}
}

void	end_flag_th(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;
	t_philo_node	*node_th;

	num_people = ph->argv[1];
	i = 0;
	while (i < num_people)
	{
		node_th = get_philo_node(&ph->thread_list, i);
		x_lock_mutex_philo(node_th);
		node_th->flag_end = true;
		x_unlock_mutex_philo(node_th);
		i++;
	}
}

bool rutine_judge_end_in_thread(t_pthread_monitor_node *end_monitor)
{
	t_mutex	*mutex_struct;
	t_philo_main *ph;

	ph = end_monitor->ph;
	mutex_struct = &end_monitor->ph->mutex_struct;
	if (is_flag_died(end_monitor))
		return (true);
	x_lock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
	if (judge_ate_all(ph, ph->argv[1]))
		return (true);
	x_unlock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
	return (false);
}

void	*end_monitor_in_thread(void *ptr)
{
	t_pthread_monitor_node	*end_monitor;

	end_monitor = (t_pthread_monitor_node *)ptr;
	while (1)
	{
		if (rutine_judge_end_in_thread(end_monitor))
			break ;
	}
	end_flag_th(end_monitor->ph);
	return (ptr);
}

static void	create_and_run_pthread_philo(t_philo_node *node_th)
{
	int	ret;

	ret = pthread_create(&node_th->thread, NULL, \
		dining_philosophers_in_thread, node_th);
	if (ret != 0)
		get_err_flag_node_th(node_th);
}


static void	create_and_run_pthread_monitor(t_pthread_monitor_node *end_monitor)
{
	int	ret;

	ret = pthread_create(&end_monitor->monitor_th, NULL, end_monitor_in_thread, end_monitor);
	if (ret != 0)
		get_err_flag_eat_monitor(&end_monitor->eat_monitor);
}

void	set_and_run_philo(t_philo_main *ph, size_t id)
{
	t_philo_node	*node_th;

	node_th = get_philo_node(&ph->thread_list, id);
	node_th->id = id;
	node_th->start_time = ph->start_time;
	node_th->flag_must_eat = ph->flag_must_eat;
	node_th->times_must_eat = ph->argv[5];
	node_th->mutex_struct = &ph->mutex_struct;
	node_th->ate_struct = &ph->ate_struct;
	node_th->died_struct = &ph->died_struct;
	create_and_run_pthread_philo(node_th);
}

// void	set_and_run_monitor(t_philo_main *ph, size_t id)
// {
// 	t_philo_node	*node_th;

// 	node_th = get_philo_node(&ph->thread_list, id);
// 	node_th->id = id;
// 	node_th->start_time = ph->start_time;
// 	node_th->flag_must_eat = ph->flag_must_eat;
// 	node_th->times_must_eat = ph->argv[5];
// 	create_and_run_pthread_philo(node_th);
// }

//create thread num_people and monitor
void	run_parallel_process(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;
	t_pthread_monitor_node	*end_monitor;

	num_people = ph->argv[1];
	end_monitor = &ph->end_monitor;
	i = 0;
	get_start_time(ph);
	//監視者スレッド作成
	create_and_run_pthread_monitor(end_monitor);
	while (i < num_people)
	{
		set_and_run_philo(ph, i);
		// set_and_run_monitor(ph, i);
		i++;
	}
	join_pthread(ph);
	if (ph->died_struct.died_flag == true)
		put_stamp(get_time_milli_sec() - ph->start_time, ph->died_struct.died_id, DIED_STR);
}
