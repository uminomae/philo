/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/24 14:31:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_hungly(t_philo *node_philo)
{
	t_philo	*node_next_philo;
	t_philo	*node_prev_philo;

	x_lock_mutex_philo(node_philo, &node_philo->mutex_philo);
	node_next_philo = node_philo->next;
	node_prev_philo = node_philo->prev;
	x_unlock_mutex_philo(node_philo, &node_philo->mutex_philo);
	x_lock_mutex_philo(node_next_philo, &node_next_philo->mutex_philo);
	if (node_next_philo->hungry == true)
	{
		x_unlock_mutex_philo(node_next_philo, &node_next_philo->mutex_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_next_philo, &node_next_philo->mutex_philo);
	x_lock_mutex_philo(node_prev_philo, &node_prev_philo->mutex_philo);
	if (node_prev_philo->hungry == true)
	{
		x_unlock_mutex_philo(node_prev_philo, &node_prev_philo->mutex_philo);
		return (true);
	}
	x_unlock_mutex_philo(node_prev_philo, &node_prev_philo->mutex_philo);
	return (false);
}

void	set_flag_end(t_ph *ph, \
			pthread_mutex_t *mtx_end, t_mutex *mtx_st)
{
	x_lock_mutex_struct(mtx_end, mtx_st);
	ph->end_st.flag_end = true;
	x_unlock_mutex_struct(mtx_end, mtx_st);
}

bool	is_end(t_end *end_st, t_mutex *mtx_st)
{
	bool	ret;

	ret = false;
	x_lock_mutex_struct(&mtx_st->mtx_end, mtx_st);
	if (end_st->flag_end == true)
		ret = true;
	x_unlock_mutex_struct(&mtx_st->mtx_end, mtx_st);
	return (ret);
}
