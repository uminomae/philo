/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:34:08 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		run_case_1person(t_philo_node *node_philo, t_fork_node *node_fork);
static void	run_case_normal(t_ph *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
static void	count_ate_in_philo(t_philo_node *node_philo);
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

static void	run_case_normal(t_ph *ph, \
			t_philo_node *node_philo, t_fork_node *node_fork)
{
	if (node_philo->id % 2 == 1)
	{
		if (!x_usleep_millisec(ph, 1))
			return ;
	}
	while (!is_end(&ph->end_struct, &ph->mutex_struct))
	{
		if (is_hungly(node_philo))
			continue ;
		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			break ;
		if (node_philo->flag_must_eat == true)
			count_ate_in_philo(node_philo);
		if (!put_state(SLEEPING, node_philo, ph->argv[4], node_philo->id))
			break ;
		if (!put_state(THINKING, node_philo, 0, node_philo->id))
			break ;
	}
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	ph->error_num = node_fork->error_num;
	ph->error_num = node_philo->error_num;
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	return ;
}

static void	count_ate_in_philo(t_philo_node *node_philo)
{
	t_mutex	*mutex_struct;

	mutex_struct = &node_philo->ph->mutex_struct;
	x_lock_mutex_philo(node_philo);
	if (node_philo->times_must_eat == node_philo->cnt)
	{
		x_unlock_mutex_philo(node_philo);
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
	x_unlock_mutex_philo(node_philo);
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
