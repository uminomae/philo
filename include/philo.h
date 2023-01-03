/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/01/03 22:18:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdbool.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include <pthread.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <signal.h>

//削除予定
#define DELAY 5000
#define FOOD 8
//

typedef struct s_ptr_node
{
	void				*ptr;
	struct s_ptr_node	*next;
}	t_ptr_node;

typedef struct s_ptr_list
{
	struct s_ptr_node	*head;
	struct s_ptr_node	*tail;
}	t_ptr_list;

typedef struct s_node
{
	size_t			data;
	pthread_mutex_t	mutex;
	struct s_node	*next;
}	t_node;

typedef struct s_list
{
	struct s_node	*head;
	struct s_node	*tail;
}	t_list;

// program(s) should take the following arguments: 
// [1]number_of_philosophers: 哲学者の数とフォークの数。
// [2]time_to_die: time_to_die ミリ秒以内に食事を開始しなかった場合、哲学者は死亡します。
// [3]time_to_eat: 哲学者が食事をするのにかかる時間。 
// [4]time_to_sleep : 哲学者が睡眠に費やす時間。
// [5][number_of_times_each_philosopher_must_eat]: すべての哲学者がnumber_of_times_each_philosopher_must_eat 回食べた場合、シミュレーションは停止します。
typedef struct s_philo
{
    // pthread_mutex_t fork[5];
    pthread_t		philo[5];
    pthread_mutex_t food_lock;
    size_t			sleep_seconds;
	size_t			argv[5];//5番目はオプション
	void			(*put_type[5])(size_t);
    size_t			id;
	struct s_list	fork_list;
	struct s_ptr_list	alloc_list;
}	t_philo;

#define NL				"\n"
#define TAKEN_FORK_STR	" has taken a fork"
#define EATING_STR		" is eating"
#define SLEEPING_STR	" is sleeping"
#define THINKING_STR	" is thinking"
#define DIED_STR		" is died"

enum e_put_type {
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
};

void    begin_philo(t_philo *ph, int argc, char **argv);
void    check_valid_values(int argc, char **argv);
//
void    init_pthread_mutex(t_philo *ph);
void    create_pthread(t_philo *ph);
void    join_pthread(t_philo *ph);
//
void *philosopher (void *ph);
void grab_fork (t_philo*, size_t, size_t, char *);
// void down_forks (t_philo*, int,  int);
void    down_forks(t_philo *ph, size_t c);

// int food_on_table ();
//
void    *dining_philosophers(void *ptr);
//
void    put_timestamp(t_philo *ph, size_t id, size_t i);
//
int		ft_isdigit(int c);
int		ph_atoi(const char *str);
//
void    put_taken_fork(size_t id);
void    put_eating(size_t id);
void    put_sleeping(size_t id);
void    put_thinking(size_t id);
void    put_died(size_t id);
//
void	add_list(t_list *list, t_ptr_list *ptr_list, size_t data);
void	*malloc_and_add_ptr_list(t_ptr_list *ptr_list, size_t size);

#endif
