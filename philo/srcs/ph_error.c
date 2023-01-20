/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/20 11:34:08 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_error(t_ph *ph)
{
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	ph->error_num = ph->mutex_struct.error_num;
	if (ph->error_num > NUM_ERR_LOW)
	{
		x_unlock_mutex_ph(&ph->mutex_ph, ph);
		return (true);
	}
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	return (false);
}

void	get_err_num_mutex(t_mutex *mutex_struct, size_t err_num)
{
	x_lock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	mutex_struct->error_num = err_num;
	x_unlock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
}

void	get_err_num_ph(t_ph *ph, size_t err_num)
{
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	ph->error_num = err_num;
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
}

void	get_err_num_fork(t_fork_node *node_fork, size_t err_num)
{
	x_lock_mutex_fork(node_fork);
	node_fork->error_num = err_num;
	x_unlock_mutex_fork(node_fork);
}

void	get_err_num_philo(t_philo_node *node_philo, size_t err_num)
{
	x_lock_mutex_philo(node_philo);
	node_philo->error_num = err_num;
	x_unlock_mutex_philo(node_philo);
}
