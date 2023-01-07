/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/07 19:03:06 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// bool	is_ate_all(t_philo *ph)
// {
// 	size_t			i;
// 	size_t			cnt;
// 	t_pthread_node	*node_th;
// 	size_t		num_people;

// 	num_people = ph->argv[1];
// 	node_th = ph->thread_list.head;
// 	cnt = 0;
// 	i = 0;
// 	while (i < num_people)
// 	{
// 		if (node_th->ate == TRUE)
// 			cnt++;
// 		node_th = node_th->next;
// 		i++;
// 	}
// 	if (cnt == num_people)
// 	{
// 		ph->monitor.ate_all = TRUE;
// 		return (TRUE);
// 	}
// 	return (FALSE);
// }

// err

// void	*monitor_in_thread(void *ptr)
// {
// 	// t_monitor	*monitor;
// 	// bool		ret;

// 	// monitor = (t_monitor *)ptr;
// 	// ret = false;
// 	// while (1)
// 	// {
// 	// // printf("%p\n", monitor);
// 	// 	// ret = is_ate_all(monitor->ph, num_people);
// 	// 	// printf("%d\n", ret);
// 	// 	// if (ret == TRUE)
// 	// 	// {
// 	// 	// 	break;
// 	// 	// }
		
// 	// 	//死んだか？
// 	// }
// 	return (ptr);
// }
