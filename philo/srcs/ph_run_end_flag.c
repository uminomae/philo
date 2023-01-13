/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_end_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 10:11:27 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end_flag_to_philo(t_philo_main *ph)
{
	size_t			i;
	size_t			num_people;
	t_philo_node	*node_philo;

	num_people = ph->argv[1];
	i = 0;
	while (i < num_people)
	{
		printf("end %zu\n", i);
		node_philo = get_philo_node(&ph->philo_list, i);
		x_lock_mutex_philo(node_philo);
		node_philo->flag_end = true;
		x_unlock_mutex_philo(node_philo);
		i++;
	}
}