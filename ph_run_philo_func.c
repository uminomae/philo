/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_philo_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/08 15:50:02 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示
//TODO 優先順位 tailだったら条件で。
static t_fork_node	*get_fork_node(t_fork_list *list, size_t c)
{
	size_t	i;
	t_fork_node	*node;

	node = list->head;
	i = 0;
	while (i < c)
	{
		node = node->next;
		i++;
	}
	return (node);
}

void	change_state_and_putstamp(size_t i, t_pthread_node *node_th, long ms, size_t id)
{
	long	time_current;

	time_current = get_time_milli_sec();
	if (time_current < 0)
		node_th->flag_err = TRUE;
	if (i != DIED)
		node_th->time[i] = time_current - node_th->start_time;
	if (put_stamp(node_th->time[i], id, *node_th->status[i]) < 0)
		node_th->flag_err = TRUE;
	if (ms != 0)
	{
		if (x_usleep_ms(ms) < 0)
			node_th->flag_err = TRUE;
	}
}

int	run_case1person(t_pthread_node	*node_th)
{
	while (1)
	{
		if (is_end_flag(node_th))
			return (1);
	}
}

static void	set_flag_died(t_philo *ph, t_pthread_node *node_th)
{
	x_pthread_mutex_lock(&ph->die_monitor.mutex, &ph->monitor);
	ph->die_monitor.time_died = get_time_milli_sec() - node_th->start_time;
	ph->die_monitor.flag_died = true;
	ph->die_monitor.died_id = node_th->id;
	x_pthread_mutex_unlock(&ph->die_monitor.mutex, &ph->monitor);
	node_th->flag_died = true;
}

bool	check_time_to_die(t_pthread_node *node_th, long time_current)
{
	if (time_current - (node_th->start_time + node_th->time[EATING]) >= (long)node_th->ph->argv[2])
	{
		set_flag_died(node_th->ph, node_th);
		return (true);
	}
	return (false);
}

bool	is_flag_died(t_pthread_node *node_th)
{
	bool	ret;

	ret = false;
	x_pthread_mutex_lock(&node_th->ph->die_monitor.mutex, &node_th->ph->monitor);
	if (node_th->ph->die_monitor.flag_died == true)
		ret = true;
	x_pthread_mutex_unlock(&node_th->ph->die_monitor.mutex, &node_th->ph->monitor);
	return (ret);
}

bool	is_end_flag(t_pthread_node *node_th)
{
	if (check_time_to_die(node_th, get_time_milli_sec()))
		return (true);
	if (is_flag_died(node_th))
		return (true);
	x_pthread_mutex_lock(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	if(is_ate_all(&node_th->ph->monitor))
		return (true);

	x_pthread_mutex_unlock(&node_th->ph->monitor.mutex, &node_th->ph->monitor);
	return(false);
}

// err処理 get_time_mille_secの失敗時
// longにargvを修正
void	*dining_philosophers_in_thread(void *ptr)
{
	t_pthread_node	*node_th;
	t_fork_node		*node_fork;

	node_th = (t_pthread_node *)ptr;
	node_fork = get_fork_node(&node_th->ph->fork_list, node_th->id);
	while (1)
	{
		if (get_time_milli_sec() < 0)
			node_th->flag_err = TRUE;
		if (node_th->ph->argv[1] == 1)
		{
			if (run_case1person(node_th))
				break ;
		}
		if (is_end_flag(node_th))
			break ;
		if (run_eating(node_th, node_fork, node_th->id, node_th->ph->argv[3]) > 0)
			break ;
		if (is_end_flag(node_th))
			break ;
		change_state_and_putstamp(SLEEPING, node_th, node_th->ph->argv[4], node_th->id);
		if (is_end_flag(node_th))
			break ;
		change_state_and_putstamp(THINKING, node_th, 0, node_th->id);
	}
	return (NULL);
}
