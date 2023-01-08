/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_philo_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/09 04:18:26 by uminomae         ###   ########.fr       */
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

void	change_state_and_putstamp(size_t i, \
		t_pthread_node *node_th, long ms, size_t id)
{
	long	time_current;

	time_current = get_time_milli_sec();
	if (time_current < 0)
		node_th->flag_err = true;
	if (i != DIED)
		node_th->time[i] = time_current - node_th->start_time;
	if (put_stamp(node_th->time[i], id, *node_th->status[i]) < 0)
		node_th->flag_err = true;
	if (ms != 0)
	{
		if (x_usleep_ms(ms) < 0)
			node_th->flag_err = true;
	}
}

int	run_case1person(t_pthread_node	*node_th)
{
	while (1)
	{
		if (judge_ate_died(node_th))
			return (1);
	}
}

void	run_rutine_philo(t_pthread_node	*node_th, t_fork_node *node_fork)
{
	while (1)
	{
		if (judge_ate_died(node_th))
			break ;
		if (run_eating(node_th, node_fork, node_th->id, \
			node_th->ph->argv[3]) > 0)
			break ;
		change_state_and_putstamp(SLEEPING, node_th, \
				node_th->ph->argv[4], node_th->id);
		change_state_and_putstamp(THINKING, node_th, 0, node_th->id);
	}
}

//TODO 優先順位 tailだったら条件で。
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
