/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:48:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_hungly(t_philo *philo_n)
{
	t_philo	*next_philo_n;
	t_philo	*prev_philo_n;

	x_lock_mtx_philo(philo_n, &philo_n->mtx_philo);
	next_philo_n = philo_n->next;
	prev_philo_n = philo_n->prev;
	x_unlock_mtx_philo(philo_n, &philo_n->mtx_philo);
	x_lock_mtx_philo(next_philo_n, &next_philo_n->mtx_philo);
	if (next_philo_n->hungry == true)
	{
		x_unlock_mtx_philo(next_philo_n, &next_philo_n->mtx_philo);
		return (true);
	}
	x_unlock_mtx_philo(next_philo_n, &next_philo_n->mtx_philo);
	x_lock_mtx_philo(prev_philo_n, &prev_philo_n->mtx_philo);
	if (prev_philo_n->hungry == true)
	{
		x_unlock_mtx_philo(prev_philo_n, &prev_philo_n->mtx_philo);
		return (true);
	}
	x_unlock_mtx_philo(prev_philo_n, &prev_philo_n->mtx_philo);
	return (false);
}

void	set_flag_end(t_ph *ph, pthread_mutex_t *mtx_end, t_mutex *mtx_st)
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
