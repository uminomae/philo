/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_run_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:52:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/14 14:06:04 by uminomae         ###   ########.fr       */
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


//idx_state:
// enum e_put_state {
// 	TAKEN_FORK = 0,
// 	EATING,
// 	SLEEPING,
// 	THINKING,
// 	DIED,
// 	PUT_TYPE_END,
// };
void	put_state(size_t idx_state, t_philo_node *node_philo, long ms, size_t id)
{
	const long	time_current = get_time_milli_sec();
	const t_philo_main *ph = node_philo->ph;
	
	if (time_current < 0)
		get_err_num_philo(node_philo, ERR_GETTEIME_MS);
	node_philo->time[idx_state] = time_current;
	if (put_stamp(node_philo->time[idx_state], id, ph->status[idx_state]) < 0)
	// if (put_stamp(node_philo->time[idx_state], id, node_philo->ph->status[idx_state]) < 0)
		get_err_num_philo(node_philo, ERR_PRINTF);

	// if (id == 0)
	// 	printf("\x1b[31m");
	// if (id == 1)
	// 	printf("\x1b[32m");
	// if (id == 2)
	// 	printf("\x1b[33m");
	// if (id == 3)
	// 	printf("\x1b[34m");
	
	// printf("-前------------------%ld\n", get_time_milli_sec());
	
	if (ms > 0)
	{
		wait_action_usleep_ms(node_philo->time[idx_state], ms);
		// if (usleep_ms(ms) < 0)
			get_err_num_philo(node_philo, ERR_USLEEP);
	}
// 	printf("-後------------------%ld\n", get_time_milli_sec());
// 	printf("\x1b[0m");
// 	printf("\n\n\n");
}

t_philo_node	*get_philo_node(t_philo_list *list_philo, size_t id)
{
	size_t			i;
	t_philo_node	*node_philo;

	node_philo = list_philo->head;
	i = 0;
	while (i < id)
	{
		node_philo = node_philo->next;
		i++;
	}
	return (node_philo);
}

t_fork_node	*get_fork_node(t_fork_list *list_fork, size_t c)
{
	size_t		i;
	t_fork_node	*node_fork;

	node_fork = list_fork->head;
	i = 0;
	while (i < c)
	{
		node_fork = node_fork->next;
		i++;
	}
	return (node_fork);
}

t_monitor_node	*get_monitor_node(t_monitor_list *list_monitor, size_t id)
{
	size_t			i;
	t_monitor_node	*node_monitor;

	node_monitor = list_monitor->head;
	i = 0;
	while (i < id)
	{
		node_monitor = node_monitor->next;
		i++;
	}
	return (node_monitor);
}