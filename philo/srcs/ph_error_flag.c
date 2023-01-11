/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/11 19:14:57 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_err_flag(t_philo_main *ph)
{
	ph->flag_err = true;
}

void	get_err_flag_node_th(t_philo_node *node)
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

void	get_err_flag_end_monitor(t_monitor_node *node)
{
	node->flag_err = true;
}

void	get_err_num(t_mutex *mutex_struct, size_t err_num)
{
	mutex_struct->error_num = err_num;
}

void	get_err_num_ph(t_philo_main *ph, size_t err_num)
{
	ph->error_num = err_num;
}