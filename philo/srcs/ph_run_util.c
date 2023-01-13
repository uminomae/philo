/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 21:53:26 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	put_stamp(long time, size_t id, const char *str)
{
	int	ret;

	ret = printf("%ld %zu %s\n", time, id, str);
	return (ret);
}

void	put_state(size_t i, t_philo_node *node_philo, long ms, size_t id)
{
	const long	time_current = get_time_milli_sec();
	
	if (time_current < 0)
		get_err_num_philo(node_philo, ERR_GETTEIME_MS);
	node_philo->time[i] = time_current;
	if (put_stamp(node_philo->time[i], id, node_philo->ph->status[i]) < 0)
		get_err_num_philo(node_philo, ERR_PRINTF);
	if (ms > 0)
	{
		if (usleep_ms(ms) < 0)
			get_err_num_philo(node_philo, ERR_USLEEP);
	}
}

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

t_monitor_node	*get_monitor_node(t_monitor_list *list_monitor, size_t id)
{
	size_t			i;
	t_monitor_node	*node_monitor;

	node_monitor = list_monitor->head;
	i = 0;
	while (i < id)
	{
		node_monitor = node_monitor->next;
		i++;
	}
	return (node_monitor);
}