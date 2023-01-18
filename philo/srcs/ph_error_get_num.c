/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_get_num.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 17:36:21 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_err_num_mutex(t_mutex *mutex_struct, size_t err_num)
{
	mutex_struct->error_num = err_num;
}

void	get_err_num_ph(t_philo_main *ph, size_t err_num)
{
	ph->error_num = err_num;
}

void	get_err_num_fork(t_fork_node *node_fork, size_t err_num)
{
	node_fork->error_num = err_num;
}

void	get_err_num_philo(t_philo_node *node_philo, size_t err_num)
{
	node_philo->error_num = err_num;
}

void	get_err_num_ptr(t_ptr_node *node_ptr, size_t err_num)
{
	node_ptr->error_num = err_num;
}
