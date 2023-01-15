/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_eating.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/16 07:31:06 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static bool	case_tail_person(t_philo_node *node_th);
static void	unlock_mutex_forks(t_philo_node *node_philo, \
		t_fork_node *node_fork);
static bool	lock_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id);
static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id);

void	*run_judge_hungry(void *ptr)
{
	t_philo_node	*node_philo;
	long	not_hungry_time;
	int		ret;
	long	total;
	long	start;

	node_philo = (t_philo_node *)ptr;
	ret = 0;
	x_lock_mutex_philo(node_philo);
	not_hungry_time = node_philo->ph->argv[3] + node_philo->ph->argv[4];
	start = node_philo->time[EATING];
	x_unlock_mutex_philo(node_philo);
	total = not_hungry_time + start;
	while(total > get_time_milli_sec())
	{
		if (total - get_time_milli_sec() > 5)
		{
			ret = usleep((total - get_time_milli_sec()) /2 );
		}
	}
	x_lock_mutex_philo(node_philo);
	if (ret < 0)
		get_err_num_ph(node_philo->ph, ERR_USLEEP);
	node_philo->hungry = true;
	x_unlock_mutex_philo(node_philo);
	return (SUCCESS);
}

bool	run_eating(t_philo_node *node_philo, \
	t_fork_node *node_fork, size_t id, long time_eat)
{
	int	ret;
	
	while(1)
	{
		x_lock_mutex_philo(node_philo);
		if (node_philo->hungry == true)
		{
			x_unlock_mutex_philo(node_philo);
			break;
		}
		x_unlock_mutex_philo(node_philo);
		// ret = usleep(100);
		// if (ret < 0)
		// 	return(ERR_NEGA_NUM);
	}
	if (!lock_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!lock_next_fork_mutex(node_philo, node_fork, id))
		return (false);
	if (!put_state(EATING, node_philo, time_eat, id))
	{
		unlock_mutex_forks(node_philo, node_fork);
		return (false);
	}
	unlock_mutex_forks(node_philo, node_fork);
	x_lock_mutex_philo(node_philo);
	node_philo->cnt++;
	x_unlock_mutex_philo(node_philo);
//
	node_philo->hungry = false;
	ret = pthread_create(&node_philo->philo_monit_th, NULL, \
			run_judge_hungry, node_philo);
	if (ret != 0)
		get_err_num_ph(node_philo->ph, ERR_PTHREAD_CREATE);
	//err　処理
	ret = pthread_detach(node_philo->philo_monit_th); 
//

	return (true);
}

// static bool	case_tail_person(t_philo_node *node_th)
// {
// 	if (node_th == node_th->ph->philo_list.tail)
// 		return (true);
// 	return (false);
// }

static void	unlock_mutex_forks(t_philo_node *node_philo, \
		t_fork_node *node_fork)
{
	t_fork_node		*node_next_fork;

	(void)node_philo;
	node_next_fork = node_fork->next;
	// if (case_tail_person(node_philo))
	// {
	// 	x_unlock_mutex_fork(node_fork);
	// 	x_unlock_mutex_fork(node_next_fork);
	// }
	// else
	// {
		x_unlock_mutex_fork(node_next_fork);
		x_unlock_mutex_fork(node_fork);
	// }
}

static bool	lock_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id)
{
	// t_fork_node	*node_next_fork;

	// x_lock_mutex_fork(node_fork);
	// node_next_fork = node_fork->next;
	// x_unlock_mutex_fork(node_fork);
	// if (case_tail_person(node_philo))
	// {
	// 	x_lock_mutex_fork(node_next_fork);
	// 	if (!put_state(TAKEN_FORK, node_philo, 0, id))
	// 	{
	// 		x_unlock_mutex_fork(node_next_fork);
	// 		return (false);
	// 	}
	// }
	// else
	// {
		x_lock_mutex_fork(node_fork);
		if (!put_state(TAKEN_FORK, node_philo, 0, id))
		{
			x_unlock_mutex_fork(node_fork);
			return (false);
		}
	// }
	return (true);
}

static bool	lock_next_fork_mutex(t_philo_node *node_philo, \
		t_fork_node *node_fork, size_t id)
{
	t_fork_node	*node_next_fork;

	node_next_fork = node_fork->next;
	// if (case_tail_person(node_philo))
	// {
	// 	x_lock_mutex_fork(node_fork);
	// 	if (!put_state(TAKEN_FORK, node_philo, 0, id))
	// 	{
	// 		x_unlock_mutex_fork(node_fork);
	// 		return (false);
	// 	}
	// }
	// else
	// {
		x_lock_mutex_fork(node_next_fork);
		if (!put_state(TAKEN_FORK, node_philo, 0, id))
		{
			x_unlock_mutex_fork(node_next_fork);
			return (false);
		}
	// }
	return (true);
}