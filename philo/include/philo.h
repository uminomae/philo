/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 01:04:46 by hioikawa          #+#    #+#             */
/*   Updated: 2023/01/20 11:46:39 by uminomae         ###   ########.fr       */
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
	size_t				error_num;
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
	pthread_mutex_t	mutex_fork;
	bool			flag_err;
	struct s_ph		*ph;
	size_t			error_num;
	struct s_fork	*next;
}	t_fork;

typedef struct s_fork_list
{
	struct s_fork	*head;
	struct s_fork	*tail;
}	t_fork_list;

typedef struct s_monitor
{
	struct s_monitor	*next;
	pthread_t			monitor_th;
	pthread_mutex_t		mutex_monitor;
	struct s_philo		*node_philo;
	bool				flag_must_eat;
	size_t				times_must_eat;
	size_t				num_people;
	struct s_ph			*ph;
}	t_monitor;

typedef struct s_end_struct
{
	bool	flag_end;
}	t_end_struct;

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
	size_t	id;
	long	time;
}	t_ate_struct;

typedef struct s_mutex
{
	pthread_mutex_t	mutex_cnt_ate;
	pthread_mutex_t	mutex_ate_all;
	pthread_mutex_t	mutex_die;
	pthread_mutex_t	mutex_end;
	size_t			error_num;
}	t_mutex;

typedef struct s_philo
{
	pthread_mutex_t	mutex_philo;
	pthread_t		philo_th;
	pthread_t		philo_monit_th;
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
	size_t			error_num;
	struct s_mutex	*mutex_struct;
	bool			hungry;
	pthread_t		philo_sleep_th;
	pthread_t		philo_eat_th;
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
	long					sleep_seconds;
	bool					flag_must_eat;
	size_t					error_num;
	size_t					argv[6];
	long					passed_time;
	size_t					id;
	struct s_fork_list		fork_list;
	struct s_philo_list		philo_list;
	struct s_monitor		monitor_node;
	struct s_ptr_list		alloc_list;
	char					*status[5];
	bool					ate_all;
	struct s_mutex			mutex_struct;
	struct s_ate_struct		ate_struct;
	struct s_die_struct		died_struct;
	struct s_end_struct		end_struct;
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
	ERR_CHECK_HUNGRY,
	ERR_PUT_STATE,
	ERR_WAIT_ACTION,
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
# define LIMIT_HUNGRY	50
# define NUM_OF_TYPES	5

enum e_put_state {
	TAKEN_FORK = 0,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	PUT_TYPE_END,
};

bool	is_valid_values(t_ph *ph, int argc, char **argv);
bool	init_mutex(t_ph *ph);
bool	build_struct_and_list(t_ph *ph, int argc);
bool	add_fork_list(t_ph *ph, t_fork_list *list, \
			t_ptr_list *ptr_list, size_t data);
bool	add_philo_list(t_ph *ph, t_philo_list *list, \
			t_ptr_list *ptr_list, size_t id);
bool	destroy_mutex(t_ph *ph);
int		usleep_ms(size_t ms);
bool	is_end(t_end_struct *end_struct, t_mutex *mutex_struct);
void	*run_rutine_philo(void *ptr);
bool	gettimeofday_millisec(t_ph *ph, long *cur_time);
bool	get_time_from_start(t_ph *ph, long *current_time);
void	*run_rutine_monitor(void *ptr);
int		put_stamp(long time, size_t id, char *state);
int		ft_isdigit(int c);
int		ph_atoi(const char *str);
char	*x_strdup(t_ptr_list *list, char *str);
bool	run_parallel_process(t_ph *ph);
void	set_and_run_monitor(t_ph *ph, size_t id);
bool	run_eating(t_philo *node_th, t_fork *node_fork, \
			size_t id, long time_eat);
bool	put_state(size_t idx_state, t_philo *node_philo, \
			long ms, size_t id);
void	*malloc_and_add_ptr_list(t_ptr_list *ptr_list, size_t size);
void	end_error(t_ph *ph);
void	end_philo(t_ph *ph);
bool	free_all(t_ph *ph);
void	get_err_num_mutex(t_mutex *mutex_struct, size_t err_num);
void	get_err_num_ph(t_ph *ph, size_t err_num);
void	get_err_num_fork(t_fork *node_fork, size_t err_num);
void	get_err_num_philo(t_philo *node_philo, size_t err_num);
bool	is_error(t_ph *ph);
void	x_lock_mutex_ph(pthread_mutex_t *mutex_ph, t_ph *ph);
void	x_unlock_mutex_ph(pthread_mutex_t *mutex_ph, t_ph *ph);
void	x_lock_mutex(pthread_mutex_t *mutex_eat, \
			t_monitor *end_monitor);
void	x_unlock_mutex(pthread_mutex_t *mutex_eat, \
			t_monitor *end_monitor);
void	x_lock_mutex_fork(t_fork *node_fork);
void	x_unlock_mutex_fork(t_fork *node_fork);
void	x_lock_mutex_philo(t_philo *node_th);
void	x_unlock_mutex_philo(t_philo *node_th);
void	x_lock_mutex_struct(pthread_mutex_t *mutex, \
			t_mutex *mutex_struct);
void	x_unlock_mutex_struct(pthread_mutex_t *mutex, \
			t_mutex *mutex_struct);
bool	x_pthread_create(t_ph *ph, pthread_t *t, \
			void *(*f)(void *), void *p);
bool	x_pthread_detach(t_ph *ph, pthread_t *thread);
bool	x_usleep_millisec(t_ph *ph, long time_ms);
bool	is_flag_died(t_monitor *eat_monitor);
void	wait_ate_person(t_philo *node_th);
void	set_flag_died(t_ph *ph, size_t id);
bool	judge_time_to_die(t_ph *ph, size_t num_people);
void	*run_judge_hungry(void *ptr);
void	run_case_1person(t_philo *node_philo, t_fork *node_fork);
t_fork	*get_fork(t_fork_list *list_fork, size_t id);
t_philo	*get_philo(t_philo_list *list_philo, size_t id);
void	set_flag_end(t_ph *ph, pthread_mutex_t *mutex_end, \
			t_mutex *mutex_struct);
void	get_err_num(t_ph *ph);
bool	put_died(t_ph *ph);
#endif
