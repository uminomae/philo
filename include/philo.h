/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/01/06 22:59:34 by uminomae         ###   ########.fr       */
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
// # define DELAY 1000
# define FOOD 10
//

typedef struct s_ptr_node
{
	void				*ptr;
	bool				flag_err;
	struct s_ptr_node	*next;
}	t_ptr_node;

typedef struct s_ptr_list
{
	struct s_ptr_node	*head;
	struct s_ptr_node	*tail;
}	t_ptr_list;

typedef struct s_pthread_node
{
	pthread_t				thread;
	size_t					id;
	long					time[4];
	char					**status[5];
	struct s_pthread_node	*next;
	struct s_philo			*ph;
	bool					flag_err;
}	t_pthread_node;

typedef struct s_pthread_list
{
	struct s_pthread_node	*head;
	struct s_pthread_node	*tail;
}	t_pthread_list;

typedef struct s_fork_node
{
	size_t				data;
	pthread_mutex_t		mutex;
	bool				flag_err;
	struct s_fork_node	*next;
}	t_fork_node;

typedef struct s_fork_list
{
	struct s_fork_node	*head;
	struct s_fork_node	*tail;
}	t_fork_list;

// program(s) should take the following arguments: 
// [1]number_of_philosophers: 哲学者の数とフォークの数。
// [2]time_to_die: time_to_die ミリ秒以内に食事を開始しなかった場合、哲学者は死亡します。
// [3]time_to_eat: 哲学者が食事をするのにかかる時間。 
// [4]time_to_sleep : 哲学者が睡眠に費やす時間。
// [5][number_of_times_each_philosopher_must_eat]: 
//すべての哲学者がnumber_of_times_each_philosopher_must_eat 回食べた場合、シミュレーションは停止します。
typedef struct s_philo
{
	long					sleep_seconds;
	bool					must_eat;
	bool					flag_err;
	size_t					argv[6];
	long					start_time;
	size_t					id;
	struct s_fork_list		fork_list;
	struct s_pthread_list	thread_list;
	struct s_ptr_list		alloc_list;
	char					*status[5];
}	t_philo;

# define NL				"\n"
# define TAKEN_FORK_STR	"has taken a fork"
# define EATING_STR		"is eating"
# define SLEEPING_STR	"is sleeping"
# define THINKING_STR	"is thinking"
# define DIED_STR		"is died"

# define FALSE		0
# define TRUE		1

enum e_put_type {
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	PUT_TYPE_END,
};

void	begin_philo(t_philo *ph, int argc, char **argv);
bool	is_invalid_values(int argc, char **argv);
void	build_struct_and_list(t_philo *ph, int argc, char **argv);
void	init_mutex(t_philo *ph);
void	run_parallel_process(t_philo *ph);
long	get_time_milli_sec(void);
void	get_start_time(t_philo *ph);

int	x_usleep_ms(size_t ms);

void	*dining_philosophers_in_thread(void *ptr);

void	put_stamp(long time, size_t id, char *str);

int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
int		ft_put_positivelong_fd(long n, int fd);
int		ph_atoi(const char *str);
char	*x_strdup(t_ptr_list *list, char *str);

void	toggle_mutex_forks(size_t flag, t_pthread_node *node_th, t_fork_list *list_fork, size_t id);
void	change_state_philosopher(size_t i, t_pthread_node *node_th, long ms, size_t id);

size_t	add_fork_list(t_fork_list *list, t_ptr_list *ptr_list, size_t data);
size_t	add_pthread_list(t_philo *ph, t_pthread_list *list, t_ptr_list *ptr_list, size_t id);
void	*malloc_and_add_ptr_list(t_ptr_list *ptr_list, size_t size);

void	end_philo(t_philo *ph);
// int		exit_error(void);
void	free_all(t_philo *ph);

void	get_err_flag(t_philo *ph);
void	get_err_flag_node_th(t_pthread_node *node);
void	get_err_flag_node_fork(t_fork_node *node);
void	get_err_flag_node_ptr(t_ptr_node *node);

bool	is_error(t_philo *ph);

#endif
