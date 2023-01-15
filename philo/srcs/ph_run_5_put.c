/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_put.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/15 14:41:38 by uminomae         ###   ########.fr       */
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
		if (is_end(&ph->end_struct, &ph->mutex_struct))
			return (IS_END_FLAG);
		if (total - get_time_milli_sec() > 5)
		{
			ret = usleep(1000);
			if (ret < 0)
				return(ERR_NEGA_NUM);
		}
	}
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

// bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct)
// {
// 	bool ret;

// 	ret = false;
// 	x_lock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
// 	if (end_struct->flag_end == true)
// 		ret = true;
// 	x_unlock_mutex_struct(&mutex_struct->mutex_end, mutex_struct);
// 	return (ret);
// }