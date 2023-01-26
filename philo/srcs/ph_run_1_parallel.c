/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_1_parallel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/26 21:16:12 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_mutex(t_ph *ph);
static bool	x_pthread_mutex_init(t_ph *ph, pthread_mutex_t *mutex);
static bool	create_thread(t_ph *ph, size_t num_people);
static bool	join_pthread(t_ph *ph);

bool	run_parallel_process(t_ph *ph)
{
	if (!init_mutex(ph))
		return (false);
	if (!create_thread(ph, ph->argv[1]))
		return (false);
	if (!join_pthread(ph))
		return (false);
	if (is_error(ph))
		return (false);
	return (true);
}

static bool	init_mutex(t_ph *ph)
{
	size_t		i;
	t_fork		*node_fork;	
	t_philo		*node_philo;
	size_t		ret;

	ret = true;
	ret &= x_pthread_mutex_init(ph, &ph->mtx_st.mtx_cnt_ate);
	ret &= x_pthread_mutex_init(ph, &ph->mtx_st.mtx_ate_all);
	ret &= x_pthread_mutex_init(ph, &ph->mtx_st.mtx_die);
	ret &= x_pthread_mutex_init(ph, &ph->mtx_st.mtx_end);
	ret &= x_pthread_mutex_init(ph, &ph->mutex_ph);
	node_fork = ph->fork_list.head;
	node_philo = ph->philo_list.head;
	i = 0;
	while (i < ph->argv[1])
	{
		ret &= x_pthread_mutex_init(ph, &node_fork->mtx_fork);
		node_fork = node_fork->next;
		ret &= x_pthread_mutex_init(ph, &node_philo->mutex_philo);
		ret &= x_pthread_mutex_init(ph, &node_philo->mutex_put);
		node_philo = node_philo->next;
		i++;
	}
	return (ret);
}

static bool	x_pthread_mutex_init(t_ph *ph, pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_init(mutex, NULL);
	if (ret != 0)
	{
		set_err_num_ph(ph, ERR_PTHREAD_MUTEX_INIT);
		return (false);
	}
	return (true);
}

static bool	create_thread(t_ph *ph, size_t num_people)
{
	size_t	i;
	t_philo	*node_philo;

	if (!gettimeofday_millisec(ph, &ph->start_time))
		return (false);
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo(&ph->philo_list, i);
		x_pthread_create(ph, &node_philo->philo_th, \
					run_rutine_philo, node_philo);
		i++;
	}
	x_pthread_create(ph, &ph->ate_all_monitor.monitor_th, \
				run_monitor_ate_all, &ph->ate_all_monitor);
	x_pthread_create(ph, &ph->err_monitor.monitor_th, \
				run_monitor_error, &ph->err_monitor);
	x_pthread_create(ph, &ph->die_monitor.monitor_th, \
				run_monitor_die, &ph->die_monitor);
	x_pthread_create(ph, &ph->hungry_monitor.monitor_th, \
				run_monitor_hungry, &ph->hungry_monitor);
	return (true);
}

static bool	join_pthread(t_ph *ph)
{
	size_t			i;
	const size_t	num_people = ph->argv[1];
	t_philo			*node_philo;

	if (pthread_join(ph->ate_all_monitor.monitor_th, NULL) != 0)
		set_err_num_ph(ph, ERR_PTHREAD_JOIN);
	if (pthread_join(ph->err_monitor.monitor_th, NULL) != 0)
		set_err_num_ph(ph, ERR_PTHREAD_JOIN);
	if (pthread_join(ph->die_monitor.monitor_th, NULL) != 0)
		set_err_num_ph(ph, ERR_PTHREAD_JOIN);
	if (pthread_join(ph->hungry_monitor.monitor_th, NULL) != 0)
		set_err_num_ph(ph, ERR_PTHREAD_JOIN);
	i = 0;
	while (i < num_people)
	{
		node_philo = get_philo(&ph->philo_list, i);
		if (pthread_join(node_philo->philo_th, NULL) != 0)
			set_err_num_ph(ph, ERR_PTHREAD_JOIN);
		i++;
	}
	if (ph->err_num > NUM_ERR_LOW)
		return (false);
	return (true);
}
