/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_5_rutine_monitor.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/13 16:19:48 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



// static void	set_flag_ate_in_philo(t_philo_list *list_philo, size_t num_people)
// {
// 	size_t			i;
// 	t_philo_node	*node_philo;

// 	node_philo = list_philo->head;
// 	i = 0;
// 	while (i < num_people)
// 	{
// 		//getnodeしてそれぞれのmutexを
// 		node_philo = get_philo_node(list_philo, i);
		
// 		x_lock_mutex_philo(node_philo);
// 		// node_philo->ate = true;
// 		node_philo->flag_end = true;
// 		x_unlock_mutex_philo(node_philo);

// 		node_philo = node_philo->next;
// 		i++;
// 	}
// 	printf("===============flag philo end\n");
// }

bool	is_flag_end(t_philo_main *ph)
{
	if (ph->flag_end == true)
		return (true);
	return (false);
}


bool	judge_ate_all(t_philo_main *ph, size_t num_people)
{
	x_lock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	if (ph->ate_struct.ate_cnt == num_people)
	{
		ph->ate_struct.ate_all = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
		// printf("===============ate_all\n");
		
		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		//flag end
		ph->flag_end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		// printf("===============end flag\n");
		
		return (true);
	}
	x_unlock_mutex_struct(&ph->mutex_struct.mutex_cnt_ate, &ph->mutex_struct);
	return (false);
}

//TODO argv[1]をinitでnum_peopleに
void	*run_rutine_monitor_in_thread(void *ptr)
{
	t_monitor_node	*node_monitor;
	t_philo_main	*ph;
	// bool			ret;
	size_t	num_people;
	long	time_current;
	bool	end;

	end = false;
	node_monitor = (t_monitor_node *)ptr;
	ph = node_monitor->ph;
	// ret = false;
	num_people = ph->argv[1];
	while (end == false)
	{
		// printf("========moni th\n");
		//ate_all?
		judge_ate_all(ph, num_people);
		// if (ret == true)
		// {
		// 	// printf("end----------------\n");
		// 	break ;
		// }
		time_current = get_time_milli_sec();
		if (time_current < 0)
			get_err_num_ph(node_monitor->ph, ERR_GETTEIMEOFDAY);
		
		x_lock_mutex_philo(node_monitor->node_philo);
		check_time_to_die(node_monitor->node_philo, time_current);
		// if (ret == true)
		// {
		// 	break;
		// }
		x_unlock_mutex_philo(node_monitor->node_philo);

		x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		if (ph->flag_end == true)
			end = true;
		x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		// flag end break
		// x_lock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		// if (is_flag_end(ph))
		// {
		// 	x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
		// 	break;
		// }
		// x_unlock_mutex_struct(&ph->mutex_struct.mutex_end, &ph->mutex_struct);
	}
	return (ptr);
}
