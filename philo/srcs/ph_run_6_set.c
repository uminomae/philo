/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:02:33 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_flag_died(t_ph *ph, size_t id)
{
	t_mutex	*mtx_st;

	mtx_st = &ph->mtx_st;
	x_lock_mutex_struct(&mtx_st->mtx_die, mtx_st);
	if (ph->died_st.died_flag == false)
	{
		ph->died_st.died_flag = true;
		ph->died_st.died_id = id;
	}
	x_unlock_mutex_struct(&mtx_st->mtx_die, mtx_st);
	x_lock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
	ph->end_st.flag_end = true;
	x_unlock_mutex_struct(&mtx_st->mtx_end, &ph->mtx_st);
}

void	set_flag_end(t_ph *ph, \
			pthread_mutex_t *mtx_end, t_mutex *mtx_st)
{
	x_lock_mutex_struct(mtx_end, mtx_st);
	ph->end_st.flag_end = true;
	x_unlock_mutex_struct(mtx_end, mtx_st);
}
