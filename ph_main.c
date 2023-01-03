/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:51:44 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/04 00:52:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	ph;

	begin_philo(&ph, argc, argv);
	init_pthread_mutex(&ph);
	create_pthread(&ph);
	join_pthread(&ph);
	put_timestamp(&ph, 1, 0);
	return (0);
}

void	put_timestamp(t_philo *ph, size_t id, size_t i)
{
	ph->put_type[i](id);
}
