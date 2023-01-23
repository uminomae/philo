/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_1_rutine_philo.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/23 12:39:04 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		run_case_1person(t_philo *node_philo, t_fork *node_fork);
static void	run_case_normal(t_ph *ph, t_philo	*node_philo, \
						t_fork *node_fork);
static void	delay_start_eating(t_ph *ph, t_philo *node_philo);
static void	count_ate_in_philo(t_philo *node_philo);

void	*run_rutine_philo(void *ptr)
{
	t_philo	*node_philo;
	t_fork	*node_fork;

	node_philo = (t_philo *)ptr;
	node_fork = get_fork(&node_philo->ph->fork_list, node_philo->id);
	node_philo->node_fork = node_fork;
	if (node_philo->ph->argv[1] == 1)
		run_case_1person(node_philo, node_fork);
	else
		run_case_normal(node_philo->ph, node_philo, node_fork);
	return (ptr);
}

void	run_case_1person(t_philo *node_philo, t_fork *node_fork)
{
	x_lock_mutex_fork(node_fork);
	if (!put_state(TAKEN_FORK, node_philo, 0, node_philo->id))
	{
		x_unlock_mutex_fork(node_fork);
		return ;
	}
	x_unlock_mutex_fork(node_fork);
	while (!is_end(&node_philo->ph->end_st, &node_philo->ph->mtx_st))
		;
	return ;
}

static void	run_case_normal(t_ph *ph, \
			t_philo *node_philo, t_fork *node_fork)
{
	delay_start_eating(ph, node_philo);
	while (!is_end(&ph->end_st, &ph->mtx_st))
	{
		if (ph->argv[1] % 2 == 1 && is_hungly(node_philo))
			continue ;
		if (!run_eating(node_philo, node_fork, node_philo->id, ph->argv[3]))
			break ;
		if (node_philo->flag_must_eat == true)
			count_ate_in_philo(node_philo);
		if (!put_state(SLEEPING, node_philo, ph->argv[4], node_philo->id))
			break ;
		if (!put_state(THINKING, node_philo, 0, node_philo->id))
			break ;
	}
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	x_lock_mutex_fork(node_fork);
	if (node_fork->err_num > NUM_ERR_LOW)
		ph->err_num = node_fork->err_num;
	x_unlock_mutex_fork(node_fork);
	if (node_philo->err_num > NUM_ERR_LOW)
		ph->err_num = node_philo->err_num;
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	return ;
}

static void	delay_start_eating(t_ph *ph, t_philo *node_philo)
{
	if (ph->argv[1] % 2 == 1 && node_philo->id != 0)
	{
		if (!x_usleep_millisec(ph, ph->argv[3] / 2))
			return ;
	}
	else
	{
		if (node_philo->id % 2 == 1)
		{
			if (!x_usleep_millisec(ph, 1))
				return ;
		}
	}
}

static void	count_ate_in_philo(t_philo *node_philo)
{
	t_mutex	*mtx_st;

	mtx_st = &node_philo->ph->mtx_st;
	x_lock_mutex_philo(node_philo);
	if (node_philo->times_must_eat == node_philo->cnt)
	{
		x_unlock_mutex_philo(node_philo);
		x_lock_mutex_struct(&mtx_st->mtx_cnt_ate, mtx_st);
		node_philo->ph->ate_st.ate_cnt++;
		x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, mtx_st);
	}
	x_unlock_mutex_philo(node_philo);
}
