/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_7_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/18 02:22:58 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_node	*get_philo_node(t_philo_list *list_philo, size_t id)
{
	size_t			i;
	t_philo_node	*node_philo;

	node_philo = list_philo->head;
	i = 0;
	while (i < id)
	{
		node_philo = node_philo->next;
		i++;
	}
	return (node_philo);
}

t_fork_node	*get_fork_node(t_fork_list *list_fork, size_t c)
{
	size_t		i;
	t_fork_node	*node_fork;

	node_fork = list_fork->head;
	i = 0;
	while (i < c)
	{
		node_fork = node_fork->next;
		i++;
	}
	return (node_fork);
}

bool	gettimeofday_millisec(t_philo_main *ph, long *cur_time)
{
	struct timeval	tp;
	long			milli_sec;
	int				ret;

	ret = gettimeofday(&tp, NULL);
	if (ret < 0)
	{
		get_err_num_ph(ph, ERR_GETTEIMEOFDAY);
		return (false);
	}
	milli_sec = tp.tv_sec * 1000;
	milli_sec += tp.tv_usec / 1000;
	*cur_time = milli_sec;
	return (true);
}

long	get_time_from_start(t_philo_main *ph)
{
	long			ret;

	if (!gettimeofday_millisec(ph, &ret))
	{
		get_err_num_ph(ph, ERR_GETTEIMEOFDAY);
		return (ERR_NEGA_NUM);
	}
	ret = ret - ph->start_time;
	return (ret);
}
