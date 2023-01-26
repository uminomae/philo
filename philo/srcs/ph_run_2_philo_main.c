/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_philo_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:39:02 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_1person(t_philo *philo_n, t_fork *fork_n);
static void	run_case_normal(t_ph *ph, t_philo *philo_n, t_fork *fork_n);
static void	delay_start_eating(t_ph *ph, t_philo *philo_n);
static void	count_ate_in_philo(t_philo *philo_n);

void	*run_rutine_philo(void *ptr)
{
	t_philo	*philo_n;
	t_fork	*fork_n;

	philo_n = (t_philo *)ptr;
	fork_n = get_fork(&philo_n->ph->fork_list, philo_n->id);
	philo_n->fork_n = fork_n;
	if (philo_n->ph->argv[1] == 1)
		run_case_1person(philo_n, fork_n);
	else
		run_case_normal(philo_n->ph, philo_n, fork_n);
	return (ptr);
}

static void	run_case_1person(t_philo *philo_n, t_fork *fork_n)
{
	x_lock_mutex_fork(fork_n);
	if (!put_state(TAKEN_FORK, philo_n, 0, philo_n->id))
	{
		x_unlock_mutex_fork(fork_n);
		return ;
	}
	x_unlock_mutex_fork(fork_n);
	while (!is_end(&philo_n->ph->end_st, &philo_n->ph->mtx_st))
		;
	return ;
}

static void	run_case_normal(t_ph *ph, \
			t_philo *philo_n, t_fork *fork_n)
{
	delay_start_eating(ph, philo_n);
	while (!is_end(&ph->end_st, &ph->mtx_st))
	{
		if (ph->argv[1] % 2 == 1 && is_hungly(philo_n))
			continue ;
		if (!run_eating(philo_n, fork_n, philo_n->id, ph->argv[3]))
			break ;
		if (is_end(&philo_n->ph->end_st, &philo_n->ph->mtx_st))
			break ;
		if (philo_n->flag_must_eat == true)
			count_ate_in_philo(philo_n);
		if (!put_state(SLEEPING, philo_n, ph->argv[4], philo_n->id))
			break ;
		if (!put_state(THINKING, philo_n, 0, philo_n->id))
			break ;
	}
	x_lock_mutex_ph(&ph->mutex_ph, ph);
	if (fork_n->err_num > NUM_ERR_LOW)
		ph->err_num = fork_n->err_num;
	if (philo_n->err_num > NUM_ERR_LOW)
		ph->err_num = philo_n->err_num;
	x_unlock_mutex_ph(&ph->mutex_ph, ph);
	return ;
}

static void	delay_start_eating(t_ph *ph, t_philo *philo_n)
{
	if (ph->argv[1] % 2 == 1 && philo_n->id != 0)
	{
		if (!x_usleep_millisec(ph, ph->argv[3] / 2))
			return ;
	}
	else
	{
		if (philo_n->id % 2 == 1)
		{
			if (!x_usleep_millisec(ph, 1))
				return ;
		}
	}
}

static void	count_ate_in_philo(t_philo *philo_n)
{
	t_mutex	*mtx_st;

	mtx_st = &philo_n->ph->mtx_st;
	x_lock_mutex_philo(philo_n, &philo_n->mutex_philo);
	if (philo_n->times_must_eat == philo_n->cnt)
	{
		x_unlock_mutex_philo(philo_n, &philo_n->mutex_philo);
		x_lock_mutex_struct(&mtx_st->mtx_cnt_ate, mtx_st);
		philo_n->ph->ate_st.ate_cnt++;
		x_unlock_mutex_struct(&mtx_st->mtx_cnt_ate, mtx_st);
	}
	else
		x_unlock_mutex_philo(philo_n, &philo_n->mutex_philo);
}
