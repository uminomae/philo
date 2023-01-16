/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_2_rutine_philo_func.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/17 00:30:58 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, \
						t_fork_node *node_fork);
static void	run_case_1person(t_philo_node	*node_philo, t_fork_node *node_fork);
static void	count_ate_in_philo(t_philo_node *node_philo);


void	*run_rutine_philo(void *ptr)
{
	t_philo_node	*node_philo;
	t_fork_node		*node_fork;

	node_philo = (t_philo_node *)ptr;
	node_fork = get_fork_node(&node_philo->ph->fork_list, node_philo->id);
	if (node_philo->ph->argv[1] == 1)
		run_case_1person(node_philo, node_fork);
	else
		run_case_normal(node_philo->ph, node_philo, node_fork);
	return (ptr);
}

static void	run_case_1person(t_philo_node	*node_philo, t_fork_node *node_fork)
{
	x_lock_mutex_fork(node_fork);
	if (!put_state(TAKEN_FORK, node_philo, 0, node_philo->id))
	{
		x_unlock_mutex_fork(node_fork);
		return ;
	}
	x_unlock_mutex_fork(node_fork);
	usleep(node_philo->ph->argv[2] * 1000);
	x_lock_mutex_philo(node_philo);
	set_flag_died(node_philo->ph, node_philo->id);
	x_unlock_mutex_philo(node_philo);
	return ;
}




void *put_sleep_think(void *ptr)
{
    t_philo_node    *node_philo;
    long time_sleep;

    node_philo = (t_philo_node *)ptr;
    time_sleep = node_philo->ph->argv[4];
//flag
    x_lock_mutex_philo(node_philo);
    node_philo->flag_sleeping = true;
    x_unlock_mutex_philo(node_philo);
    if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
        return (ptr);
        //flag
    x_lock_mutex_philo(node_philo);
    node_philo->flag_sleeping = false;
    x_unlock_mutex_philo(node_philo);
    if (!put_state(THINKING, node_philo, 0, node_philo->id))
        return (ptr);
    return (ptr);
}



static void run_case_normal(t_philo_main *ph, t_philo_node  *node_philo, t_fork_node *node_fork)
{
    const long time_eat = ph->argv[3];
    // const long time_sleep = ph->argv[4];
    int ret;
    
    if (node_philo->id % 2 == 1)
        usleep(100);
    while (1)
    {
        while(1)
        {
            x_lock_mutex_philo(node_philo);
            if (node_philo->flag_sleeping == false)
            {
                x_unlock_mutex_philo(node_philo);
                break;
            }
            x_unlock_mutex_philo(node_philo);
        // ret = usleep(100);
        // if (ret < 0)
        //  return(ERR_NEGA_NUM);
        }
        if (!run_eating(node_philo, node_fork, node_philo->id, time_eat))
            break ;
        if (ph->flag_must_eat == true)
            count_ate_in_philo(node_philo);
        
		x_pthread_create(node_philo->ph, &node_philo->philo_monit_th, run_judge_hungry, node_philo);


        ret = pthread_create(&node_philo->philo_sleep_th, NULL, \
                put_sleep_think, node_philo);
        if (ret != 0)
            get_err_num_ph(node_philo->ph, ERR_PTHREAD_CREATE);
        //err　処理
        ret = pthread_detach(node_philo->philo_sleep_th);
        // if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
        //  break;
        // if (!put_state(THINKING, node_philo, 0, node_philo->id))
        //  break;
    }
    return ;
}

// static void	run_case_normal(t_philo_main *ph, t_philo_node	*node_philo, t_fork_node *node_fork)
// {
// 	const long time_eat = ph->argv[3];
// 	const long time_sleep = ph->argv[4];

// 	if (node_philo->id % 2 == 1)
// 		usleep(100);
// 	while (1)
// 	{
// 		if (!run_eating(node_philo, node_fork, node_philo->id, time_eat))
// 			break ;
// 		if (ph->flag_must_eat == true)
// 			count_ate_in_philo(node_philo);
// 		if (!put_state(SLEEPING, node_philo, time_sleep, node_philo->id))
// 			break;
// 		if (!put_state(THINKING, node_philo, 0, node_philo->id))
// 			break;
// 	}
// 	return ;
// }

static void	count_ate_in_philo(t_philo_node *node_philo)
{
	t_mutex	*mutex_struct;

	mutex_struct = &node_philo->ph->mutex_struct;
	if (node_philo->times_must_eat == node_philo->cnt)
	{
		x_lock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
		node_philo->ph->ate_struct.ate_cnt++;
		x_unlock_mutex_struct(&mutex_struct->mutex_cnt_ate, mutex_struct);
	}
}
