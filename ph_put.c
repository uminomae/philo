/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:50:06 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/04 00:50:39 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_taken_fork(size_t id)
{
	printf("%zu", id);
	printf(TAKEN_FORK_STR);
	printf(NL);
}

void	put_eating(size_t id)
{
	printf("%zu", id);
	printf(EATING_STR);
	printf(NL);
}

void	put_sleeping(size_t id)
{
	printf("%zu", id);
	printf(SLEEPING_STR);
	printf(NL);
}

void	put_thinking(size_t id)
{
	printf("%zu", id);
	printf(THINKING_STR);
	printf(NL);
}

void	put_died(size_t id)
{
	printf("%zu", id);
	printf(DIED_STR);
	printf(NL);
}
