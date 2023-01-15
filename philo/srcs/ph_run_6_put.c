/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_6_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/16 04:25:35 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//time, id, state:
//Ex.1673650735348 0 is sleeping
int	put_stamp(long time, size_t id, const char *state)
{
	int	ret;

	ret = printf("%ld %zu %s\n", time, id, state);
	return (ret);
}

int	wait_action_usleep_ms(t_philo_main *ph, long start, size_t wait_ms)
{
	int		ret;
	long	total;

	ret = 0;
	total = wait_ms + start;
	while(total >= get_time_milli_sec())
	{
		// if (total - get_time_milli_sec() < 10)
		// {
			if (is_end(&ph->end_struct, &ph->mutex_struct))
				return (IS_END_FLAG);
		// }
		if (total - get_time_milli_sec() > 5)
		{
			ret = usleep(100);
			if (ret < 0)
				return(ERR_NEGA_NUM);
		}
	// printf("------wait %ld, %ld\n", wait_ms, total);
	}
	// printf("------wait end\n");
	return (SUCCESS);
}

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
	// printf("------hungry \n");
	while(total >= get_time_milli_sec())
	{
		if (total - get_time_milli_sec() > 5)
		{
			ret = usleep(100);
		}
	}
	x_lock_mutex_philo(node_philo);
	if (ret < 0)
		get_err_num_ph(node_philo->ph, ERR_USLEEP);
	node_philo->hungry = true;
	x_unlock_mutex_philo(node_philo);
	return (SUCCESS);
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
	int		ret;

	ret = 0;
	if (time_current < 0)
		get_err_num_philo(node_philo, ERR_GETTEIME_MS);
	node_philo->time[idx_state] = time_current;
	if (is_end(&node_philo->ph->end_struct, &node_philo->ph->mutex_struct))
		return (false);
	if (put_stamp(node_philo->time[idx_state], id, ph->status[idx_state]) < 0)
		get_err_num_philo(node_philo, ERR_PRINTF);
//	
	if (idx_state == EATING)
	{
		node_philo->hungry = false;
		ret = pthread_create(&node_philo->philo_monit_th, NULL, \
				run_judge_hungry, node_philo);
		if (ret != 0)
			get_err_num_ph(node_philo->ph, ERR_PTHREAD_CREATE);
		//err　処理
		ret = pthread_detach(node_philo->philo_monit_th); 
	}
//
	if (ms > 0)
	{
		ret = wait_action_usleep_ms(node_philo->ph, node_philo->time[idx_state], ms);
		if (ret == IS_END_FLAG)
			return (false);
		if (ret == ERR_NEGA_NUM)
			get_err_num_philo(node_philo, ERR_USLEEP);
	}
	return (true);
}
