/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/01/26 21:34:19 by uminomae         ###   ########.fr       */
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
	size_t				err_num;
	struct s_ptr_node	*next;
}	t_ptr_node;

typedef struct s_ptr_list
{
	struct s_ptr_node	*head;
	struct s_ptr_node	*tail;
}	t_ptr_list;

typedef struct s_fork
{
	size_t			data;
	pthread_mutex_t	mtx_fork;
	bool			flag_err;
	struct s_ph		*ph;
	size_t			err_num;
	struct s_fork	*next;
}	t_fork;

typedef struct s_fork_list
{
	struct s_fork	*head;
	struct s_fork	*tail;
}	t_fork_list;

typedef struct s_monitor
{
	pthread_t			monitor_th;
	bool				flag_must_eat;
	size_t				num_people;
	struct s_ph			*ph;
	struct s_mutex		*mtx_st;
}	t_monitor;

typedef struct s_end
{
	bool	flag_end;
}	t_end;

typedef struct s_die
{
	bool	died_flag;
	long	time_died;
	size_t	died_id;
}	t_die;

typedef struct s_ate
{
	size_t	ate_cnt;
	bool	ate_all;
	size_t	id;
	long	time;
}	t_ate;

typedef struct s_mutex
{
	pthread_mutex_t	mtx_cnt_ate;
	pthread_mutex_t	mtx_ate_all;
	pthread_mutex_t	mtx_die;
	pthread_mutex_t	mtx_end;
	size_t			err_num;
}	t_mutex;

typedef struct s_philo
{
	pthread_mutex_t	mutex_philo;
	pthread_mutex_t	mutex_put;
	pthread_t		philo_th;
	size_t			id;
	long			time[5];
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_ph		*ph;
	bool			flag_must_eat;
	size_t			times_must_eat;
	size_t			cnt;
	bool			ate;
	bool			flag_wait_ate;
	size_t			err_num;
	struct s_mutex	*mtx_st;
	bool			hungry;
	struct s_fork	*node_fork;
}	t_philo;

typedef struct s_philo_list
{
	struct s_philo	*head;
	struct s_philo	*tail;
}	t_philo_list;

// program(s) should take the following arguments: 
// [1]number_of_philosophers: 
// [2]time_to_die:
// [3]time_to_eat: 
// [4]time_to_sleep : 
// [5][number_of_times_each_philosopher_must_eat]: 
typedef struct s_ph
{
	pthread_mutex_t			mutex_ph;
	long					sleep_time;
	bool					flag_must_eat;
	size_t					err_num;
	size_t					argv[6];
	size_t					id;
	struct s_fork_list		fork_list;
	struct s_philo_list		philo_list;
	struct s_ptr_list		alloc_list;
	struct s_monitor		ate_all_monitor;
	struct s_monitor		err_monitor;
	struct s_monitor		die_monitor;
	struct s_monitor		hungry_monitor;
	char					*status[5];
	struct s_mutex			mtx_st;
	struct s_ate			ate_st;
	struct s_die			died_st;
	struct s_end			end_st;
	long					start_time;
}	t_ph;

enum e_err_type {
	NUM_ERR_LOW = 10,
	ERR_PTHREAD_UNLOCK,
	ERR_PTHREAD_LOCK,
	ERR_ADD_PHILO_LIST,
	ERR_ADD_FORK_LIST,
	ERR_ADD_MONITOR_LIST,
	ERR_PTHREAD_JOIN,
	ERR_PTHREAD_CREATE,
	ERR_PTHREAD_DESTROY,
	ERR_PTHREAD_DETACH,
	ERR_GETTEIMEOFDAY,
	ERR_ARGV_NULL,
	ERR_ATOI,
	ERR_PRINTF,
	ERR_USLEEP,
	ERR_MALLOC,
	ERR_PTHREAD_MUTEX_INIT,
	ERR_STRDUP,
	ERR_IS_DIGIT,
	ERR_judge_hungry,
	ERR_PUT_STATE,
	ERR_WAIT_ACTION,
	ERR_PUT_DIED,
	ERR_TYPE_END,
};

# define NL				"\n"
# define TAKEN_FORK_STR	"has taken a fork"
# define EATING_STR		"is eating"
# define SLEEPING_STR	"is sleeping"
# define THINKING_STR	"is thinking"
# define DIED_STR		"is died"
# define ERR_STR		"error\n"

# define LOCK			1
# define UNLOCK			0
# define ERROR			1
# define SUCCESS		0
# define ERR_NEGA_NUM	-1
# define IS_END_FLAG	1
# define HUNGRY			1
# define OK				0
# define NUM_OF_TYPES	5
# define WAIT_REGULARLY	100

enum e_put_state {
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	PUT_TYPE_END,
};

bool	is_valid_values(t_ph *ph, int argc, char **argv);
bool	build_struct_and_list(t_ph *ph, int argc);
bool	run_parallel_process(t_ph *ph);
void	end_error(t_ph *ph);
void	end_philo(t_ph *ph);

bool	add_fork_list(t_ph *ph, t_fork_list *list, \
			t_ptr_list *ptr_list, size_t data);
bool	add_philo_list(t_ph *ph, t_philo_list *list, \
			t_ptr_list *ptr_list, size_t id);

bool	is_error(t_ph *ph);

bool	is_hungly(t_philo *node_philo);
void	set_flag_end(t_ph *ph, pthread_mutex_t *mtx_end, t_mutex *mtx_st);
bool	is_flag_died(t_monitor *eat_monitor);

bool	put_died(t_ph *ph);

t_fork	*get_fork(t_fork_list *list_fork, size_t id);
t_philo	*get_philo(t_philo_list *list_philo, size_t id);
bool	gettimeofday_millisec(t_ph *ph, long *cur_time);
bool	get_time_from_start(t_ph *ph, long *current_time);

int		ft_isdigit(int c);

void	set_err_num_mutex(t_mutex *mtx_st, size_t err_num);
void	set_err_num_ph(t_ph *ph, size_t err_num);
void	set_err_num_fork(t_fork *node_fork, size_t err_num);
void	set_err_num_philo(t_philo *node_philo, size_t err_num);

bool	free_all(t_ph *ph);
void	*malloc_and_add_ptr_list(t_ptr_list *ptr_list, size_t size);

void	x_lock_mutex_fork(t_fork *node_fork);
void	x_unlock_mutex_fork(t_fork *node_fork);
void	x_lock_mutex_philo(t_philo *node_philo, pthread_mutex_t *mtx);
void	x_unlock_mutex_philo(t_philo *node_philo, pthread_mutex_t *mtx);
void	x_lock_mutex_ph(pthread_mutex_t *mutex_ph, t_ph *ph);
void	x_unlock_mutex_ph(pthread_mutex_t *mutex_ph, t_ph *ph);
void	x_lock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mtx_st);
void	x_unlock_mutex_struct(pthread_mutex_t *mutex, t_mutex *mtx_st);

bool	x_pthread_create(t_ph *ph, pthread_t *t, \
			void *(*f)(void *), void *p);
bool	x_pthread_detach(t_ph *ph, pthread_t *thread);
bool	x_usleep_millisec(t_ph *ph, long time_ms);
bool	x_usleep_microsec(t_ph *ph, long time_microsec);

bool	destroy_mutex(t_ph *ph);

bool	put_state(size_t idx_state, t_philo *node_philo, long ms, size_t id);
bool	is_end(t_end *end_st, t_mutex *mtx_st);

void	*run_rutine_philo(void *ptr);
void	*run_monitor_ate_all(void *ptr);
void	*run_monitor_error(void *ptr);
void	*run_monitor_die(void *ptr);
void	*run_monitor_hungry(void *ptr);
bool	run_eating(t_philo *node_philo, t_fork *node_fork, \
					size_t id, long time_eat);

int		ph_atoi(const char *str);
char	*x_strdup(t_ptr_list *list, char *str);

#endif
