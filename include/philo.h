/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/01/08 15:45:57 by uminomae         ###   ########.fr       */
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
// # define FOOD 10
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

typedef struct s_pthread_node
{
	pthread_t				thread;
	size_t					id;
	long					time[5];
	char					**status[5];
	struct s_pthread_node	*next;
	struct s_philo			*ph;
	bool					flag_err;
	bool					flag_died;
	long					start_time;
	bool					flag_must_eat;
	size_t					times_must_eat;
	size_t					cnt;
	bool					ate;

}	t_pthread_node;

typedef struct s_pthread_list
{
	struct s_pthread_node	*head;
	struct s_pthread_node	*tail;
}	t_pthread_list;

typedef struct s_die_monitor
{
	pthread_mutex_t			mutex;
	struct s_philo			*ph;
	bool					flag_err;
	bool					flag_died;
	long					time_died;
	size_t					died_id;
}	t_die_monitor;

typedef struct s_monitor
{
	pthread_mutex_t			mutex;
	struct s_philo			*ph;
	bool					flag_err;
	size_t					ate_cnt;
	bool					ate_all;
	bool					flag_died;
}	t_monitor;

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
	bool					flag_must_eat;
	bool					flag_err;
	size_t					argv[6];
	long					start_time;
	size_t					id;
	struct s_fork_list		fork_list;
	struct s_pthread_list	thread_list;
	struct s_ptr_list		alloc_list;
	struct s_monitor		monitor;
	char					*status[5];
	bool					ate_all;
	// bool					flag_died;
	struct s_die_monitor	die_monitor;
}	t_philo;

# define NL				"\n"
# define TAKEN_FORK_STR	"has taken a fork"
# define EATING_STR		"is eating"
# define SLEEPING_STR	"is sleeping"
# define THINKING_STR	"is thinking"
# define DIED_STR		"is died"
# define ERR_STR		"error"

# define FALSE		0
# define TRUE		1
# define LOCK		1
# define UNLOCK		0
# define ERROR		1
# define SUCCESS	0
# define ATE_ALL	1
# define END_FLAG	3

enum e_put_type {
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	PUT_TYPE_END,
};

void	begin_philo(t_philo *ph, int argc, char **argv);
bool	is_valid_values(int argc, char **argv);

void	build_struct_and_list(t_philo *ph, int argc, char **argv);
void	init_mutex(t_philo *ph);
void	run_parallel_process(t_philo *ph);
long	get_time_milli_sec(void);
void	get_start_time(t_philo *ph);

int		x_usleep_ms(size_t ms);

void	*dining_philosophers_in_thread(void *ptr);

int		put_stamp(long time, size_t id, char *str);

int		ft_isdigit(int c);
// void	ft_putstr_fd(char *s, int fd);
// int		ft_put_positivelong_fd(long n, int fd);
int		ph_atoi(const char *str);
char	*x_strdup(t_ptr_list *list, char *str);

// void	toggle_mutex(size_t flag, t_monitor *monitor, t_fork_node *node_fork);
// void	eating(t_pthread_node *node_th, t_fork_node *node_fork, size_t id);
int	run_eating(t_pthread_node *node_th, t_fork_node *node_fork, size_t id, long time_eat);

// void	toggle_mutex(size_t flag, t_fork_node *node_fork);
// void	toggle_mutex(size_t flag, t_pthread_node *node_th, t_fork_node *node_fork, size_t id);

// void	toggle_mutex(size_t flag, t_pthread_node *node_th, t_fork_list *list_fork, size_t id);
void	change_state_and_putstamp(size_t i, t_pthread_node *node_th, long ms, size_t id);

size_t	add_fork_list(t_fork_list *list, t_ptr_list *ptr_list, size_t data);
size_t	add_pthread_list(t_philo *ph, t_pthread_list *list, t_ptr_list *ptr_list, size_t id);
void	*malloc_and_add_ptr_list(t_ptr_list *ptr_list, size_t size);

void	end_philo(t_philo *ph);
void	end_error(t_philo *ph);
void	free_all(t_philo *ph);

void	get_err_flag(t_philo *ph);
void	get_err_flag_node_th(t_pthread_node *node);
void	get_err_flag_node_fork(t_fork_node *node);
void	get_err_flag_node_ptr(t_ptr_node *node);
void	get_err_flag_monitor(t_monitor *node);

bool	is_error(t_philo *ph);

// t_fork_node	*get_fork_node(t_fork_list *list, size_t c);

// void	lock_mutex(pthread_mutex_t *mutex, t_monitor *monitor);
// void	unlock_mutex(pthread_mutex_t *mutex, t_monitor *monitor);
void	x_pthread_mutex_lock(pthread_mutex_t *mutex, t_monitor *monitor);
void	x_pthread_mutex_unlock(pthread_mutex_t *mutex, t_monitor *monitor);



void	destroy_mutex(t_philo *ph);
bool	is_flag_died(t_pthread_node *node_th);
bool	check_time_to_die(t_pthread_node *node_th, long time_current);
bool	is_end_flag(t_pthread_node *node_th);
bool	is_ate_all(t_monitor *monitor);
bool	check_ate_all(t_monitor *monitor, size_t num_people);
// bool	check_ate_all(t_monitor *monitor, t_fork_node *node_fork, size_t num_people);
// bool	is_ate_all(t_monitor *monitor, t_fork_node *node_fork);

#endif
