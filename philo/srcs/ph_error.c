/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:01:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_error(t_ph *ph)
{
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	ph->err_num = ph->mtx_st.err_num;
	if (ph->err_num > NUM_ERR_LOW)
	{
		x_unlock_mutex_ph(&ph->mutex_ph, ph);
		return (true);
	}
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	return (false);
}

void	set_err_num_mutex(t_mutex *mtx_st, size_t err_num)
{
	mtx_st->err_num = err_num;
}

void	set_err_num_ph(t_ph *ph, size_t err_num)
{
	ph->err_num = err_num;
}

void	set_err_num_fork(t_fork *node_fork, size_t err_num)
{
	node_fork->err_num = err_num;
}

void	set_err_num_philo(t_philo *node_philo, size_t err_num)
{
	node_philo->err_num = err_num;
}
