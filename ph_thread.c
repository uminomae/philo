#include "philo.h"

void    init_pthread_mutex(t_philo *ph)
{
    size_t i;
    size_t num_philo;
	t_node *node;

	node = ph->fork_list.head;
    num_philo = ph->argv[1];
    pthread_mutex_init(&ph->food_lock, NULL);
    i = 0;
    while (i < num_philo)
    {
		// printf("pthre_mu\n");
        pthread_mutex_init(&node->mutex, NULL);
		node = node->next;
        i++;
    }
}

void    create_pthread(t_philo *ph)
{
    size_t i;
    size_t num_philo;

    num_philo = ph->argv[1];
    i = 0; 
    while (i < num_philo)
    {
        ph->id = i;
        pthread_create(&ph->philo[i], NULL, dining_philosophers, ph);
        i++;
    }
}

void    join_pthread(t_philo *ph)
{
    size_t i;
    size_t num_philo;

    num_philo = ph->argv[1];
    i = 0;
    while (i < num_philo)
    {
        pthread_join(ph->philo[i], NULL);
        i++;
    }
}
