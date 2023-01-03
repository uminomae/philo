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

static t_pthread_node *get_pthread_node(t_pthread_list *list_th, size_t c)
{
    size_t	i;
    t_pthread_node	*node_th;

	node_th = list_th->head;
    i = 0;
    while(i < c)
    {
        // printf("get_node_thread\n");
        node_th = node_th->next;
        i++;
    }
    return (node_th);
}

void    create_pthread(t_philo *ph)
{
    size_t i;
    size_t num_philo;
    int ret;
    // pthread_t thread;
    t_pthread_node *node_th;

    num_philo = ph->argv[1];
    i = 0; 
    while (i < num_philo)
    {
        ph->id = i;
        node_th = get_pthread_node(&ph->thread_list, i);
        ret = pthread_create(&node_th->thread, NULL, dining_philosophers, ph);
        // printf("cr_thread\n");
        // ret = pthread_create(&ph->philo[i], NULL, dining_philosophers, ph);
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
    t_pthread_node *node_th;

    num_philo = ph->argv[1];
    i = 0;
    while (i < num_philo)
    {
        node_th = get_pthread_node(&ph->thread_list, i);
        ret = pthread_join(node_th->thread, NULL);
        // ret = pthread_join(ph->philo[i], NULL);
        if (ret != 0)
            exit(1);
        i++;
    }
}
