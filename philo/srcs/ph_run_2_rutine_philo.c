/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 03:05:57 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		run_case_1person(t_philo_node *node_philo, t_fork_node *node_fork);
static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
static bool	is_hungly(t_philo_node *node_philo);

void	*run_rutine_philo(void *ptr)
{
	t_philo_node	*node_philo;
	t_fork_node		*node_fork;

	node_philo = (t_philo_node *)ptr;
	node_fork = get_fork_node(&node_philo->ph->fork_list, node_philo->id);
	node_philo->node_fork = node_fork;
	if (node_philo->ph->argv[1] == 1)
		run_case_1person(node_philo, node_fork);
	else
		run_case_normal(node_philo->ph, node_philo, node_fork);
	return (ptr);
}

void	run_case_1person(t_philo_node *node_philo, t_fork_node *node_fork)
{
	x_lock_mutex_fork(node_fork);
	if (!put_state(TAKEN_FORK, node_philo, 0, node_philo->id))
	{
		x_unlock_mutex_fork(node_fork);
		return ;
	}
	x_unlock_mutex_fork(node_fork);
	while (!is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		;
	return ;
}

static void	run_case_normal(t_philo_main *ph, \
			t_philo_node *node_philo, t_fork_node *node_fork)
{
	while (!is_end(&ph->end_struct, &ph->mutex_struct))
	{
		if (is_hungly(node_philo))
			continue ;
		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			return ;
		if (!put_state(SLEEPING, node_philo, ph->argv[4], node_philo->id))
			return ;
		if (!put_state(THINKING, node_philo, 0, node_philo->id))
			return ;
	}
	return ;
}

static bool	is_hungly(t_philo_node *node_philo)
{
	t_philo_node	*node_next_philo;
	t_philo_node	*node_prev_philo;

	x_lock_mutex_philo(node_philo);
	node_next_philo = node_philo->next;
	node_prev_philo = node_philo->prev;
	x_unlock_mutex_philo(node_philo);
	x_lock_mutex_philo(node_next_philo);
	if (node_next_philo->hungry == true)
	{
		x_unlock_mutex_philo(node_next_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_next_philo);
	x_lock_mutex_philo(node_prev_philo);
	if (node_prev_philo->hungry == true)
	{
		x_unlock_mutex_philo(node_prev_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_prev_philo);
	return (false);
}
