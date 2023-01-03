#include "philo.h"

void    init_pthread_mutex(t_philo *ph)
{
    size_t i;
    size_t number_of_philosophers;
	t_node *node;

	node = ph->fork_list.head;
    number_of_philosophers = ph->argv[1];
    pthread_mutex_init (&ph->food_lock, NULL);
    i = 0;
    while (i < number_of_philosophers)
    {
		// printf("pthre_mu\n");
        pthread_mutex_init (&node->mutex, NULL);
		node = node->next;
        i++;
    }
}

void    create_pthread(t_philo *ph)
{
    size_t i;
    size_t number_of_philosophers;

    number_of_philosophers = ph->argv[1];
    i = 0; 
    while (i < number_of_philosophers)
    {
        ph->id = i;
        pthread_create(&ph->philo[i], NULL, dining_philosophers, ph);
        i++;
    }
}

void    join_pthread(t_philo *ph)
{
    size_t i;
    size_t number_of_philosophers;

    number_of_philosophers = ph->argv[1];
    i = 0;
    while (i < number_of_philosophers)
    {
        pthread_join (ph->philo[i], NULL);
        i++;
    }
}

// void    init_pthread_mutex(t_philo *ph)
// {
//     size_t i;
//     size_t number_of_philosophers;

//     number_of_philosophers = ph->argv[1];
//     pthread_mutex_init (&ph->food_lock, NULL);
//     i = 0;
//     while (i < number_of_philosophers)
//     {
//         pthread_mutex_init (&ph->fork[i], NULL);
//         i++;
//     }
// }

// void    create_pthread(t_philo *ph)
// {
//     size_t i;
//     size_t number_of_philosophers;

//     number_of_philosophers = ph->argv[1];
//     i = 0; 
//     while (i < number_of_philosophers)
//     {
//         ph->id = i;
//         pthread_create(&ph->philo[i], NULL, dining_philosophers, ph);
//         i++;
//     }
// }

// void    join_pthread(t_philo *ph)
// {
//     size_t i;
//     size_t number_of_philosophers;

//     number_of_philosophers = ph->argv[1];
//     i = 0;
//     while (i < number_of_philosophers)
//     {
//         pthread_join (ph->philo[i], NULL);
//         i++;
//     }
// }
