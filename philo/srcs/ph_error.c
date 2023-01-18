/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_get_num.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/19 02:06:20 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_error(t_philo_main *ph)
{
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	ph->error_num = ph->mutex_struct.error_num;
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	if (ph->error_num > NUM_ERR_LOW)
		return (true);
	return (false);
}

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
