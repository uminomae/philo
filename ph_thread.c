#include "philo.h"

void    init_pthread_mutex(t_philo *ph)
{
    size_t i;
    size_t num_philo;
	t_node *node;
    int ret;

	node = ph->fork_list.head;
    num_philo = ph->argv[1];
    ret = pthread_mutex_init(&ph->food_lock, NULL);
    if (ret != 0)
        exit(1);
    i = 0;
    while (i < num_philo)
    {
        ret = pthread_mutex_init(&node->mutex, NULL);
        if (ret != 0)
            exit(1);
		node = node->next;
        i++;
    }
}

void    create_pthread(t_philo *ph)
{
    size_t i;
    size_t num_philo;
    int ret;

    num_philo = ph->argv[1];
    i = 0; 
    while (i < num_philo)
    {
        ph->id = i;
        ret = pthread_create(&ph->philo[i], NULL, dining_philosophers, ph);
        if (ret != 0)
            exit(1);
        i++;
    }
}

void    join_pthread(t_philo *ph)
{
    size_t i;
    size_t num_philo;
    int ret;

    num_philo = ph->argv[1];
    i = 0;
    while (i < num_philo)
    {
        ret = pthread_join(ph->philo[i], NULL);
        if (ret != 0)
            exit(1);
        i++;
    }
}
