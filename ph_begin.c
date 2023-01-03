/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_begin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:21:53 by uminomae          #+#    #+#             */
/*   Updated: 2023/01/03 23:51:09 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void init_struct_s_philo(t_philo *ph)
{
    // memset(ph, 0, sizeof(struct s_philo));
    memset(ph, 0, sizeof(t_philo));
}

static void    convert_argv_to_int(t_philo *ph, int argc, char **argv)
{
    int i;

    i = 0;
    while (i < argc)
    {
        ph->argv[i] = (size_t)ph_atoi(argv[i]);
        i++;
    }
}

static void make_fork_list(t_philo *ph)
{
    size_t  id_fork;

    id_fork = 0;
    while(id_fork < ph->argv[1])
    {
        add_list(&ph->fork_list, &ph->alloc_list, id_fork);
        id_fork++;
    }
}

static void make_pthread_list(t_philo *ph)
{
    size_t  id_th;

    id_th = 0;
    while(id_th < ph->argv[1])
    {
        add_pthread_list(&ph->thread_list, &ph->alloc_list, id_th);
        id_th++;
    }
}
static void	make_function_ptr_array(t_philo *ph)
{
    ph->put_type[TAKEN_FORK] =  put_taken_fork;
    ph->put_type[EATING] =  put_eating;
    ph->put_type[SLEEPING] =  put_sleeping;
    ph->put_type[THINKING] =  put_thinking;
    ph->put_type[DIED] =  put_died;
}

void    begin_philo(t_philo *ph, int argc, char **argv)
{
    check_valid_values(argc, argv);
    init_struct_s_philo(ph);
    convert_argv_to_int(ph, argc, argv);
    ph->sleep_seconds = ph->argv[4];
    make_fork_list(ph);
    make_pthread_list(ph);
    make_function_ptr_array(ph);
    if (ph->argv[1] == 1){
        //時間経過後にdied
        put_timestamp(ph, 1, DIED);
        exit(0);
    }
}