/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_dining_philo_func.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 15:49:05 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork_node	*get_fork_node(t_fork_list *list, size_t c)
{
	size_t		i;
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

void	put_state(size_t i, \
		t_pthread_node *node_th, long ms, size_t id)
{
	long	time_current;

	time_current = get_time_milli_sec();
	if (time_current < 0)
		node_th->flag_err = true;
	node_th->time[i] = time_current - node_th->start_time;
	if (put_stamp(node_th->time[i], id, *node_th->status[i]) < 0)
		node_th->flag_err = true;
	if (ms != 0)
	{
		if (usleep_ms(ms) < 0)
			node_th->flag_err = true;
	}
}

int	run_case1person(t_pthread_node	*node_th)
{
	while (1)
	{
		if (check_time_to_die(node_th, get_time_milli_sec()))
			return (1);
	}
}

void	run_rutine_philo(t_pthread_node	*node_th, t_fork_node *node_fork)
{
	while (1)
	{
		x_lock_mutex_philo(node_th);
		if (node_th->flag_end == true)
		{
			x_unlock_mutex_philo(node_th);
			break ;
		}
		x_unlock_mutex_philo(node_th);

		count_ate_person(node_th);
		if (check_time_to_die(node_th, get_time_milli_sec()))
			break ;
		count_ate_in_eat_monitor(node_th);
		
		if (run_eating(node_th, node_fork, node_th->id, \
			node_th->ph->argv[3]) > 0)
			break ;
		put_state(SLEEPING, node_th, \
				node_th->ph->argv[4], node_th->id);
		put_state(THINKING, node_th, 0, node_th->id);
	}
}

void	*dining_philosophers_in_thread(void *ptr)
{
	t_pthread_node	*node_th;
	t_fork_node		*node_fork;

	node_th = (t_pthread_node *)ptr;
	node_fork = get_fork_node(&node_th->ph->fork_list, node_th->id);
	if (node_th->ph->argv[1] == 1)
		run_case1person(node_th);
	else
		run_rutine_philo(node_th, node_fork);
	return (NULL);
}
