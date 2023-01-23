/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 23:42:07 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
