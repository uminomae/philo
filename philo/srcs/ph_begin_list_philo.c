/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin_list_philo.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:50:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:46:44 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*init_philo(t_ptr_list *ptr_list);
static void		make_first_philo(t_philo_list *list, t_philo *node);
static void		add_last_philo(t_philo_list *list, t_philo *node);

bool	add_philo_list(t_ph *ph, t_philo_list *philo_list, \
						t_ptr_list *ptr_list, size_t id)
{
	t_philo	*philo_n;

	philo_n = init_philo(ptr_list);
	if (philo_n == NULL)
	{
		set_err_num_ph(ph, ERR_ADD_PHILO_LIST);
		return (false);
	}
	philo_n->id = id;
	philo_n->ph = ph;
	philo_n->flag_must_eat = ph->flag_must_eat;
	philo_n->times_must_eat = ph->argv[5];
	philo_n->time[EATING] = 0;
	if (philo_list->head == NULL)
		make_first_philo(philo_list, philo_n);
	else
		add_last_philo(philo_list, philo_n);
	return (true);
}

static t_philo	*init_philo(t_ptr_list *ptr_list)
{
	t_philo	*node;

	node = (t_philo *)malloc_and_add_ptr_list(ptr_list, \
				sizeof(t_philo));
	if (node == NULL)
		return (NULL);
	memset(node, 0, sizeof(t_philo));
	return (node);
}

static void	make_first_philo(t_philo_list *list, t_philo *node)
{
	list->head = node;
	list->tail = node;
	node->next = list->head;
	node->prev = list->tail;
}

static void	add_last_philo(t_philo_list *list, t_philo *node)
{
	list->tail->next = node;
	node->prev = list->tail;
	node->next = list->head;
	list->tail = node;
}
