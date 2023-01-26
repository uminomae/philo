/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:39:02 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*get_philo(t_philo_list *list_philo, size_t id)
{
	size_t	i;
	t_philo	*philo_n;

	philo_n = list_philo->head;
	i = 0;
	while (i < id)
	{
		philo_n = philo_n->next;
		i++;
	}
	return (philo_n);
}

t_fork	*get_fork(t_fork_list *list_fork, size_t id)
{
	size_t	i;
	t_fork	*fork_n;

	fork_n = list_fork->head;
	i = 0;
	while (i < id)
	{
		fork_n = fork_n->next;
		i++;
	}
	return (fork_n);
}

bool	gettimeofday_millisec(t_ph *ph, long *cur_time)
{
	struct timeval	tp;
	long			milli_sec;
	int				ret;

	ret = gettimeofday(&tp, NULL);
	if (ret < 0)
	{
		set_err_num_ph(ph, ERR_GETTEIMEOFDAY);
		return (false);
	}
	milli_sec = tp.tv_sec * 1000;
	milli_sec += tp.tv_usec / 1000;
	*cur_time = milli_sec;
	return (true);
}

bool	get_time_from_start(t_ph *ph, long *current_time)
{
	long	ret;

	if (!gettimeofday_millisec(ph, &ret))
	{
		set_err_num_ph(ph, ERR_GETTEIMEOFDAY);
		return (false);
	}
	*current_time = ret - ph->start_time;
	return (true);
}
