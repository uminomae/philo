/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_4_dining_philo_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 13:30:55 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_1person(t_philo_node	*node_philo)
{
	usleep(node_philo->ph->argv[2] * 1000);
	x_lock_mutex_philo(node_philo);
	set_flag_died(node_philo->ph, node_philo->id);
	x_unlock_mutex_philo(node_philo);
	return ;
}

bool	is_required_times_ate(t_philo_node *node_th, size_t cnt)
{
	if (node_th->flag_must_eat == true && \
		node_th->times_must_eat == cnt)
		return (true);
	return (false);
}

void	count_ate_in_philo(t_philo_node *node_philo)
{
	t_mutex				*mutex_struct;

	mutex_struct = &node_philo->ph->mutex_struct;
	if (is_required_times_ate(node_philo, node_philo->cnt))
	{
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
}

//idx_state:
// enum e_put_state {
// 	TAKEN_FORK = 0,
// 	EATING,
// 	SLEEPING,
// 	THINKING,
// 	DIED,
// 	PUT_TYPE_END,
// };
bool	put_state(size_t idx_state, t_philo_node *node_philo, long ms, size_t id)
{
	const long	time_current = get_time_milli_sec();
	const t_philo_main *ph = node_philo->ph;
	
	if (time_current < 0)
		get_err_num_philo(node_philo, ERR_GETTEIME_MS);
	node_philo->time[idx_state] = time_current;
	if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		return (false);
	if (put_stamp(node_philo->time[idx_state], id, ph->status[idx_state]) < 0)
		get_err_num_philo(node_philo, ERR_PRINTF);
	if (ms > 0)
	{
		if(!wait_action_usleep_ms(node_philo->time[idx_state], ms))
			get_err_num_philo(node_philo, ERR_USLEEP);
	}
	return (true);
}

bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct)
{
	bool ret;

	ret = false;
	x_lock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	if (end_struct->flag_end == true)
		ret = true;
	x_unlock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
	return (ret);
}

void	run_rutine_philo_dining(t_philo_main *ph, t_philo_node	*node_philo, t_fork_node *node_fork)
{
	const long time_eat = ph->argv[3];
	const long time_sleep = ph->argv[4];
	t_mutex *mutex_struct;
	t_end_struct *end_struct;

	mutex_struct = &ph->mutex_struct;
	end_struct = &ph->end_struct;
	while (1)
	{
		if (is_end(end_struct, mutex_struct))
			break ;
		if (!run_eating(node_philo, node_fork, node_philo->id, time_eat))
			break ;
		if (ph->flag_must_eat == true)
			count_ate_in_philo(node_philo);
		if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
			break;
		if (!put_state(THINKING, node_philo, 0, node_philo->id))
			break;
	}
	return ;
}

void	*run_rutine_philo(void *ptr)
{
	t_philo_node	*node_philo;
	t_fork_node		*node_fork;

	node_philo = (t_philo_node *)ptr;
	node_fork = get_fork_node(&node_philo->ph->fork_list, node_philo->id);
	if (node_philo->ph->argv[1] == 1)
		run_case_1person(node_philo);
	else
		run_rutine_philo_dining(node_philo->ph, node_philo, node_fork);
	return (ptr);
}
