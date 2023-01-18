/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_get_num.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/19 01:05:50 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_err_num_mutex(t_mutex *mutex_struct, size_t err_num)
{
	// x_lock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
	mutex_struct->error_num = err_num;
	// x_unlock_mutex_struct(&mutex_struct->mutex_ate_all, mutex_struct);
}

void	get_err_num_ph(t_philo_main *ph, size_t err_num)
{
	// x_lock_mutex_ph(&ph->mutex_ph, ph);
	ph->error_num = err_num;
	// x_unlock_mutex_ph(&ph->mutex_ph, ph);
}

void	get_err_num_fork(t_fork_node *node_fork, size_t err_num)
{
	// x_lock_mutex_fork(node_fork);
	node_fork->error_num = err_num;
	// x_unlock_mutex_fork(node_fork);
}

void	get_err_num_philo(t_philo_node *node_philo, size_t err_num)
{
	// x_lock_mutex_philo(node_philo);
	node_philo->error_num = err_num;
	// x_unlock_mutex_philo(node_philo);
}

