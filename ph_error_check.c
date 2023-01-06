/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:21:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/06 22:54:57 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_error_list_fork(t_philo *ph)
{
	t_fork_node	*node_fork;
	size_t	i;

	node_fork = ph->fork_list.head;
	i = 0;
	while (i < ph->id)
	{
		if (node_fork->flag_err == TRUE)
		{
			ph->flag_err = TRUE;
			return ;
		}
		node_fork = node_fork->next;
		i++;
	}
	return ;
}

bool	is_error(t_philo *ph)
{
	check_error_list_fork(ph);
	if (ph->flag_err == TRUE)
		return (TRUE);
	return (FALSE);
}