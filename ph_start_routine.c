/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 01:04:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/04 16:10:23 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	food_on_table(t_philo *ph);
static void	toggle_mutex_forks(t_list *list, size_t c, size_t j);


//食べる＞食べる時間経過させる＞眠る＞眠る時間経過させる＞起きる（考え開始時刻？考え中はいつでも食べられる？）
//if 最後の食事の"開始"時刻から経過　＞die
//※死は10ミリ秒以内に表示
//if must_eat回食べたら ＞ exit(0)
void	*dining_philosophers(void *ptr)
{
	size_t	f;
	t_philo	*ph;
	int		ret;

	ph = (t_philo *)ptr;
	printf ("%zu done thinking\n", ph->id);
	printf("run\n");
	while (1)
	{
		f = food_on_table(ph);
		if (f == 0)
			break ;
		if (ph->id == 1)
			sleep (ph->sleep_seconds);
		toggle_mutex_forks(&ph->fork_list, ph->id, 1);
		//   gettimeofday(&ph->thread_list->tv, NULL);
		//   printf("%ld %06d\n", tv.tv_sec, tv.tv_usec);
		put_timestamp(ph, ph->id, EATING);
		ret = usleep (DELAY * (FOOD - f + 1));
		if (ret != 0)
			exit(1);
		toggle_mutex_forks(&ph->fork_list, ph->id, 0);
	}
	printf ("%zu done eating\n", ph->id);
	return (NULL);
}

static void	lock_mutex(t_node *node)
{
	int	ret;

	ret = pthread_mutex_lock(&node->mutex);
	if (ret != 0)
		exit(1);
}

static void	unlock_mutex(t_node *node)
{
	int	ret;

	ret = pthread_mutex_unlock(&node->mutex);
	if (ret != 0)
		exit(1);
}

static t_node	*get_node(t_list *list, size_t c)
{
	size_t	i;
	t_node	*node;

	node = list->head;
	i = 0;
	while (i < c)
	{
		node = node->next;
		i++;
	}
	return (node);
}

static void	toggle_mutex_forks(t_list *list, size_t c, size_t flag)
{
	size_t	i;
	t_node	*node_fork;

	i = 0;
	node_fork = get_node(list, i);
	if (flag == TRUE)
	{
		lock_mutex(node_fork);
		lock_mutex(node_fork->next);
		printf ("fork's mutex lock: got fork %zu\n", c);
	}
	else if (flag == FALSE)
	{
		unlock_mutex(node_fork);
		unlock_mutex(node_fork->next);
		printf ("fork's mutex unlock %zu\n", c);
	}
}

static int	food_on_table(t_philo *ph)
{
	static int	food = FOOD;
	int			myfood;

	pthread_mutex_lock (&ph->food_lock);
	if (food > 0)
		food--;
	myfood = food;
	pthread_mutex_unlock (&ph->food_lock);
	return (myfood);
}
