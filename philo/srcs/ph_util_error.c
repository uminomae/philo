/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_util_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:39:02 by uminomae         ###   ########.fr       */
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

void	set_err_num_fork(t_fork *fork_n, size_t err_num)
{
	fork_n->err_num = err_num;
}

void	set_err_num_philo(t_philo *philo_n, size_t err_num)
{
	philo_n->err_num = err_num;
}
