/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/10 22:09:54 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_error_list_fork(t_philo *ph)
{
	t_fork_node	*node_fork;
	size_t		i;

	node_fork = ph->fork_list.head;
	i = 0;
	while (i < ph->id)
	{
		if (node_fork->flag_err == true)
		{
			ph->flag_err = true;
			return ;
		}
		node_fork = node_fork->next;
		i++;
	}
	return ;
}

static void	check_error_list_th(t_philo *ph)
{
	t_pthread_node	*node_th;
	size_t			i;

	node_th = ph->thread_list.head;
	i = 0;
	while (i < ph->id)
	{
		if (node_th->flag_err == true)
		{
			ph->flag_err = true;
			return ;
		}
		node_th = node_th->next;
		i++;
	}
	return ;
}

static void	check_error_list_ptr(t_philo *ph)
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

static void	check_error_end_monitor(t_philo *ph)
{
	if (ph->end_monitor.flag_err == true)
		ph->flag_err = true;
	return ;
}

bool	is_error(t_philo *ph)
{
	check_error_list_fork(ph);
	check_error_list_th(ph);
	check_error_list_ptr(ph);
	check_error_end_monitor(ph);
	if (ph->flag_err == true)
		return (true);
	return (false);
}
