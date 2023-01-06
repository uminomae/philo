/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 21:28:32 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_error(void)
{
	return (-1);
}

void	process_error(t_philo *ph)
{
	ph->flag_err = TRUE;
}

void	process_error_node_th(t_pthread_node *node)
{
	node->flag_err = TRUE;
}

void end_philo(t_philo *ph)
{
	free_all(ph);
}
