/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/19 00:08:05 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_error_num_ptr(t_philo_main *ph);
static void	get_error_num_list_fork(t_philo_main *ph);
static void	get_error_num_list_philo(t_philo_main *ph);

void	get_err_num(t_philo_main *ph)
{
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	ph->error_num = ph->mutex_struct.error_num;
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	get_error_num_ptr(ph);
	get_error_num_list_fork(ph);
	get_error_num_list_philo(ph);
}

bool	is_error(t_philo_main *ph)
{
	// ph->error_num = ph->mutex_struct.error_num;
	// get_error_num_ptr(ph);
	// get_error_num_list_fork(ph);
	// get_error_num_list_philo(ph);
	if (ph->error_num > NUM_ERR_LOW)
		return (true);
	return (false);
}

static void	get_error_num_ptr(t_philo_main *ph)
{
	t_ptr_node	*node_ptr;
	size_t		i;

	node_ptr = ph->alloc_list.head;
	i = 0;
	while (i < ph->argv[1])
	{
		x_lock_mutex_ph(&ph->mutex_ph, ph);
		if (node_ptr->error_num > NUM_ERR_LOW)
		{
			// x_lock_mutex_ph(&ph->mutex_ph, ph);
			ph->error_num = node_ptr->error_num;
			x_unlock_mutex_ph(&ph->mutex_ph, ph);
			return ;
		}
		x_unlock_mutex_ph(&ph->mutex_ph, ph);
		node_ptr = node_ptr->next;
		i++;
	}
	return ;
}

static void	get_error_num_list_fork(t_philo_main *ph)
{
	t_fork_node	*node_fork;
	size_t		i;

	node_fork = ph->fork_list.head;
	i = 0;
	while (i < ph->argv[1])
	{
		x_lock_mutex_fork(node_fork);
		if (node_fork->error_num > NUM_ERR_LOW)
		{
			x_lock_mutex_ph(&ph->mutex_ph, ph);
			ph->error_num = node_fork->error_num;
			x_unlock_mutex_ph(&ph->mutex_ph, ph);
			x_unlock_mutex_fork(node_fork);
			return ;
		}
		x_unlock_mutex_fork(node_fork);
		node_fork = node_fork->next;
		i++;
	}
	return ;
}

static void	get_error_num_list_philo(t_philo_main *ph)
{
	t_philo_node	*node_philo;
	size_t			i;

	node_philo = ph->philo_list.head;
	i = 0;
	while (i < ph->argv[1])
	{
		// printf("----get %ld", node_philo->error_num);
		x_lock_mutex_philo(node_philo);
		if (node_philo->error_num > NUM_ERR_LOW)
		{
			x_lock_mutex_ph(&ph->mutex_ph, ph);
			ph->error_num = node_philo->error_num;
			x_unlock_mutex_ph(&ph->mutex_ph, ph);
			x_unlock_mutex_philo(node_philo);
			return ;
		}
		x_unlock_mutex_philo(node_philo);
		node_philo = node_philo->next;
		i++;
	}
	return ;
}
