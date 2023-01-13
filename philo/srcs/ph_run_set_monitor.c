/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_set_monitor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 09:41:35 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static t_monitor_node	*get_monitor_node(t_monitor_list *list_monitor, size_t id)
{
	size_t			i;
	t_monitor_node	*node_monitor;

	node_monitor = list_monitor->head;
	i = 0;
	while (i < id)
	{
		node_monitor = node_monitor->next;
		i++;
	}
	return (node_monitor);
}


bool	judge_ate_all(t_philo_main *ph, size_t num_people)
{
	x_lock_mutex_struct(&ph->mutex_struct.mutex_ate_all, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt == num_people)
	{
		ph->ate_struct.ate_all = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_ate_all, &ph->mutex_struct);
		return (true);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_ate_all, &ph->mutex_struct);

	return (false);
}

bool rutine_judge_end_in_thread(t_monitor_node *end_monitor)
{
	// t_mutex	*mutex_struct;
	// t_philo_main *ph;

	// ph = end_monitor->ph;
	// mutex_struct = &end_monitor->ph->mutex_struct;
	if (is_flag_died(end_monitor))
		return (true);
	// x_lock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
	// if (judge_ate_all(ph, ph->argv[1]))
	// 	return (true);
	// x_unlock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
	return (false);
}

static void	set_flag_ate(t_philo_node *node_philo)
{
	x_lock_mutex_philo(node_philo);
	node_philo->ate = true;
	x_unlock_mutex_philo(node_philo);
	x_lock_mutex_philo(node_philo);
	node_philo->flag_end = true;
	x_unlock_mutex_philo(node_philo);
}


static void	set_flag_ate_in_philo(t_philo_list *list_philo, size_t num_people)
{
	size_t			i;
	t_philo_node	*node_philo;

	node_philo = list_philo->head;
	i = 0;
	while (i < num_people)
	{
		//getnodeしてそれぞれのmutexを
		node_philo = get_philo_node(list_philo, i);

		set_flag_ate(node_philo);
		node_philo = node_philo->next;
		i++;
	}
}


//TODO argv[1]をinitでnum_peopleに
void	*run_rutine_monitor_in_thread(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	bool			ret;

	node_monitor = (t_monitor_node *)ptr;
	ph = node_monitor->ph;
	while (1)
	{
		//ate_all?
		ret = judge_ate_all(ph, ph->argv[1]);
		//ate_flag_each_philo
		if (ret == true)
		{
			set_flag_ate_in_philo(&ph->philo_list, ph->argv[1]);
		}

		//died? time to eat
		//flag_die_each philo
		// if (rutine_judge_end_in_thread(node_monitor))
		// 	break ;
	}
	// end_flag_th(end_monitor->ph);
	return (ptr);
}



static void	create_and_run_pthread_monitor(t_monitor_node *node_monitor)
{
	int	ret;

	ret = pthread_create(&node_monitor->monitor_th, NULL, run_rutine_monitor_in_thread, node_monitor);
	if (ret != 0)
		get_err_flag_eat_monitor(&node_monitor->eat_monitor);
}

void	set_and_run_monitor(t_philo_main *ph, size_t id)
{
	t_monitor_node	*node_monitor;

	node_monitor = get_monitor_node(&ph->monitor_list, id);
	node_monitor->id = id;
	node_monitor->start_time = ph->start_time;
	node_monitor->flag_must_eat = ph->flag_must_eat;
	node_monitor->times_must_eat = ph->argv[5];
	node_monitor->mutex_struct = &ph->mutex_struct;
	node_monitor->ate_struct = &ph->ate_struct;
	node_monitor->died_struct = &ph->died_struct;
	create_and_run_pthread_monitor(node_monitor);
}
