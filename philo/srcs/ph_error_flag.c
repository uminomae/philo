/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/10 17:02:40 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_err_flag(t_philo *ph)
{
	ph->flag_err = true;
}

void	get_err_flag_node_th(t_pthread_node *node)
{
	node->flag_err = true;
}

void	get_err_flag_node_fork(t_fork_node *node)
{
	node->flag_err = true;
}

void	get_err_flag_node_ptr(t_ptr_node *node)
{
	node->flag_err = true;
}

void	get_err_flag_eat_monitor(t_eat_monitor *node)
{
	node->flag_err = true;
}
