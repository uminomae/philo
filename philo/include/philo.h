/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/01/13 17:53:07 by uminomae         ###   ########.fr       */
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
	pthread_mutex_t		mutex_fork;
	bool				flag_err;
	struct s_philo_main	*ph;
	size_t				error_num;
	struct s_fork_node	*next;
}	t_fork_node;

typedef struct s_fork_list
{
	struct s_fork_node	*head;
	struct s_fork_node	*tail;
}	t_fork_list;

typedef struct s_die_monitor
{
	struct s_philo_main			*ph;
	bool					flag_err;
}	t_die_monitor;

typedef struct s_eat_monitor
{
	struct s_philo_main			*ph;
	bool					flag_err;
}	t_eat_monitor;

typedef struct s_monitor_node
{
	struct s_monitor_node	*next;
	pthread_t				monitor_th;
	pthread_mutex_t			mutex_monitor;
	struct s_philo_node		*node_philo;
	size_t					id;
	struct s_eat_monitor	eat_monitor;
	struct s_die_monitor	die_monitor;
	long					start_time;
	bool					flag_must_eat;
	size_t					times_must_eat;
	bool					flag_err;
	struct s_philo_main		*ph;
	long					time[5];
	// char					**status[5];
	struct s_mutex			*mutex_struct;
	struct s_ate_struct		*ate_struct;
	struct s_die_struct		*died_struct;
} 	t_monitor_node;

typedef struct s_monitor_list
{
	struct s_monitor_node	*head;
	struct s_monitor_node	*tail;
}	t_monitor_list;

typedef struct s_die_struct
{
	bool	died_flag;
	long	time_died;
	size_t	died_id;
}	t_die_struct;

typedef struct s_ate_struct
{
	size_t	ate_cnt;
	bool	ate_all;
}	t_ate_struct;

typedef struct s_mutex
{
	pthread_mutex_t			mutex_cnt_ate;
	pthread_mutex_t			mutex_ate_all;
	pthread_mutex_t			mutex_die;
	pthread_mutex_t			mutex_time_eat_start;
	pthread_mutex_t			mutex_end;
	size_t					error_num;
}	t_mutex;

typedef struct s_philo_node
{
	pthread_mutex_t			mutex_philo;
	pthread_t				philo_th;
	size_t					id;
	long					time[5];
	// char					*status[5];
	struct s_philo_node		*next;
	struct s_philo_main		*ph;
	bool					flag_err;
	bool					flag_died;
	bool					flag_end;
	long					start_time;
	bool					flag_must_eat;
	size_t					times_must_eat;
	size_t					cnt;
	bool					ate;
	bool					flag_wait_ate;
	struct s_mutex			*mutex_struct;
	struct s_ate_struct		*ate_struct;
	struct s_die_struct		*died_struct;
}	t_philo_node;

typedef struct s_philo_list
{
	struct s_philo_node	*head;
	struct s_philo_node	*tail;
}	t_philo_list;

// program(s) should take the following arguments: 
// [1]number_of_philosophers: 
// [2]time_to_die:
// [3]time_to_eat: 
// [4]time_to_sleep : 
// [5][number_of_times_each_philosopher_must_eat]: 
typedef struct s_philo_main
{
	long					sleep_seconds;
	bool					flag_must_eat;
	bool					flag_err;
	size_t					error_num;
	size_t					argv[6];
	long					start_time;
	long					passed_time;
	size_t					id;
	struct s_fork_list		fork_list;
	struct s_philo_list		philo_list;
	struct s_monitor_list	monitor_list;
	struct s_ptr_list		alloc_list;
	char					*status[5];
	bool					ate_all;
	bool					flag_end;
	struct s_monitor_node		end_monitor;
	struct s_eat_monitor	*eat_monitor;
	struct s_die_monitor	*die_monitor;
	struct s_mutex			mutex_struct;
	struct s_ate_struct		ate_struct;
	struct s_die_struct		died_struct;
}	t_philo_main;

enum e_err_type {
	NUM_ERR_LOW = 10,
	NUM_ERR_TYPE_START,
	ERR_PTHREAD_UNLOCK,
	ERR_PTHREAD_LOCK,
	ERR_ADD_PHILO_LIST,
	ERR_ADD_FORK_LIST,
	ERR_ADD_MONITOR_LIST,
	ERR_PTHREAD_JOIN,
	ERR_PTHREAD_CREATE,
	ERR_PTHREAD_DESTROY,
	ERR_GETTEIMEOFDAY,
	ERR_ARGV_NULL,
	ERR_ATOI,
	ERR_TYPE_END,
};

# define NL				"\n"
# define TAKEN_FORK_STR	"has taken a fork"
# define EATING_STR		"is eating"
# define SLEEPING_STR	"is sleeping"
# define THINKING_STR	"is thinking"
# define DIED_STR		"is died"
# define ERR_STR		"error\n"
// # define NUM_ERR_LOW	11


# define LOCK		1
# define UNLOCK		0
# define ERROR		1
# define SUCCESS	0

enum e_put_type {
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	PUT_TYPE_END,
};

bool	is_valid_values(t_philo_main *ph, int argc, char **argv);
int		build_struct_and_list(t_philo_main *ph, int argc);
void	init_mutex(t_philo_main *ph);

long	get_time_milli_sec(void);
void	get_start_time(t_philo_main *ph);
int		usleep_ms(size_t ms);

void	*run_rutine_dining_in_thread(void *ptr);
t_fork_node	*get_fork_node(t_fork_list *list, size_t c);
t_philo_node	*get_philo_node(t_philo_list *list_philo, size_t id);
void	*run_rutine_monitor_in_thread(void *ptr);
t_monitor_node	*get_monitor_node(t_monitor_list *list_monitor, size_t id);
bool	is_flag_end(t_philo_main *ph);

int		put_stamp(long time, size_t id, const char *str);

int		ft_isdigit(int c);
int		ph_atoi(const char *str);
char	*x_strdup(t_ptr_list *list, char *str);

void	run_parallel_process(t_philo_main *ph);
void	set_and_run_philo(t_philo_main *ph, size_t id);
void	set_and_run_monitor(t_philo_main *ph, size_t id);


int		run_eating(t_philo_node *node_th, \
		t_fork_node *node_fork, size_t id, long time_eat);
void	put_state(size_t i, \
		t_philo_node *node_th, long ms, size_t id);

// size_t	add_fork_list(t_fork_list *list, t_ptr_list *ptr_list, size_t data);
size_t	add_fork_list(t_philo_main *ph, t_fork_list *list, t_ptr_list *ptr_list, size_t data);
size_t	add_philo_list(t_philo_main *ph, t_philo_list *list, \
		t_ptr_list *ptr_list, size_t id);
size_t	add_monitor_list( \
			t_philo_main *ph, t_monitor_list *monitor_list, t_ptr_list *ptr_list, size_t id);

void	*malloc_and_add_ptr_list(t_ptr_list *ptr_list, size_t size);

void	end_error(t_philo_main *ph);
void	end_philo(t_philo_main *ph);
void	free_all(t_philo_main *ph);

void	get_err_flag(t_philo_main *ph);
void	get_err_flag_node_th(t_philo_node *node);
void	get_err_flag_node_fork(t_fork_node *node);
void	get_err_flag_node_ptr(t_ptr_node *node);
void	get_err_flag_eat_monitor(t_eat_monitor *node);
void	get_err_flag_end_monitor(t_monitor_node *node);
void	get_err_num(t_mutex *mutex_struct, size_t err_num);
void	get_err_num_ph(t_philo_main *ph, size_t err_num);
void	get_err_num_fork(t_fork_node *node_fork, size_t err_num);
bool	is_error(t_philo_main *ph);

void	x_lock_mutex(pthread_mutex_t *mutex_eat, t_monitor_node *end_monitor);
void	x_unlock_mutex(pthread_mutex_t *mutex_eat, t_monitor_node *end_monitor);
void	x_lock_mutex_fork(t_fork_node *node_fork);
void	x_unlock_mutex_fork(t_fork_node *node_fork);
void	x_lock_mutex_philo(t_philo_node *node_th);
void	x_unlock_mutex_philo(t_philo_node *node_th);
void	x_lock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mutex_struct);
void	x_unlock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mutex_struct);

void	destroy_mutex(t_philo_main *ph);
bool	is_flag_died(t_monitor_node *eat_monitor);

bool	check_time_to_die(t_philo_node *node_th, long time_current);
// bool	judge_ate_all(t_philo_main *ph, size_t num_people);
void	wait_ate_person(t_philo_node *node_th);
bool	is_required_times_ate(t_philo_node *node_th, size_t cnt);
void	count_ate_in_philo(t_philo_node *node_th);


#endif
