/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 14:01:51 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_pthread_node	*get_pthread_node(t_pthread_list *list_th, size_t id)
{
	size_t			i;
	t_pthread_node	*node_th;

	node_th = list_th->head;
	i = 0;
	while (i < id)
	{
		node_th = node_th->next;
		i++;
	}
	return (node_th);
}

void	create_pthread(t_philo *ph)
{
	size_t			i;
	size_t			num_philo;
	int				ret;
	t_pthread_node	*node_th;

	num_philo = ph->argv[1];
	i = 0;
	while (i < num_philo)
	{
		node_th = get_pthread_node(&ph->thread_list, i);
		node_th->id = i;
		ret = pthread_create(&node_th->thread, NULL, dining_philosophers_in_thread, node_th);
		if (ret != 0)
			exit(1);
		i++;
	}
}

void	join_pthread(t_philo *ph)
{
	size_t			i;
	size_t			num_philo;
	int				ret;
	t_pthread_node	*node_th;

	num_philo = ph->argv[1];
	i = 0;
	while (i < num_philo)
	{
		node_th = get_pthread_node(&ph->thread_list, i);
		ret = pthread_join(node_th->thread, NULL);
		if (ret != 0)
			exit(1);
		i++;
	}
}
