/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 18:24:41 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_error_list_ptr(t_philo_main *ph)
{
	t_ptr_node	*node_ptr;
	size_t		i;

	node_ptr = ph->alloc_list.head;
	i = 0;
	while (i < ph->id)
	{
		if (node_ptr->flag_err == true)
		{
			ph->flag_err = true;
			return ;
		}
		node_ptr = node_ptr->next;
		i++;
	}
	return ;
}

// static void	check_error_end_monitor(t_philo_main *ph)
// {
// 	if (ph->end_monitor.flag_err == true)
// 		ph->flag_err = true;
// 	return ;
// }


static void	check_error_num_list_fork(t_philo_main *ph)
{
	t_fork_node	*node_fork;
	size_t		i;

	node_fork = ph->fork_list.head;
	i = 0;
	while (i < ph->id)
	{
		if (node_fork->error_num > NUM_ERR_LOW)
		{
			ph->error_num = node_fork->error_num;
			return ;
		}
		node_fork = node_fork->next;
		i++;
	}
	return ;
}

static void	check_error_num_list_philo(t_philo_main *ph)
{
	t_philo_node	*node_philo;
	size_t		i;

	node_philo = ph->philo_list.head;
	i = 0;
	while (i < ph->id)
	{
		if (node_philo->error_num > NUM_ERR_LOW)
		{
			ph->error_num = node_philo->error_num;
			return ;
		}
		node_philo = node_philo->next;
		i++;
	}
	return ;
}

static void check_error_num(t_philo_main *ph)
{
	ph->error_num = ph->mutex_struct.error_num;
	check_error_num_list_fork(ph);
	check_error_num_list_philo(ph);
}

bool	is_error(t_philo_main *ph)
{
	check_error_list_ptr(ph);
	// check_error_end_monitor(ph);
	check_error_num(ph);
	if (ph->flag_err == true)
		return (true);
	if (ph->error_num > 10)
		return (true);
	return (false);
}
