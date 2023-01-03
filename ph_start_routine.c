#include "philo.h"

static int food_on_table(t_philo *ph);

// void    grab_forks(t_philo *ph, size_t phil, size_t c, char *hand)
// {
//     size_t	i;
//     t_node	*node;

// 	node = ph->fork_list.head;
//     i = 0;
//     while(i < c)
//     {
//         node = node->next;
//         i++;
//     }
//     pthread_mutex_lock(&node->mutex);
// 	pthread_mutex_lock(&node->next->mutex);
//     printf ("Philosopher %zu: got %s fork %zu\n", phil, hand, c);
// }
  	
// void	down_forks(t_philo *ph, size_t c)
// {
// 	size_t	i;
//     t_node	*node;

// 	node = ph->fork_list.head;
//     i = 0;
//     while(i < c)
//     {
//         node = node->next;
//         i++;
//     }
//     pthread_mutex_unlock(&node->mutex);
//     pthread_mutex_unlock(&node->next->mutex);
// }

void toggle_mutex_forks(t_philo *ph, size_t c, size_t j) {
    size_t	i;
    t_node	*node;

	node = ph->fork_list.head;
    i = 0;
    while(i < c)
    {
        node = node->next;
        i++;
    }
    if (j == 1)
    {
        pthread_mutex_lock(&node->mutex);
        pthread_mutex_lock(&node->next->mutex);
        printf ("fork's mutex lock:got LR-hand fork %zu\n", c);
    }else if (j == 0)
    {
        pthread_mutex_unlock(&node->mutex);
        pthread_mutex_unlock(&node->next->mutex);
        printf ("fork's mutex unlock %zu\n", c);
    }

} 

void    *dining_philosophers(void *ptr)
{
	// size_t	right_fork;
	size_t	f;
    t_philo *ph;

    ph = (t_philo *)ptr;
    printf ("Philosopher %zu is done thinking and now ready to eat.\n", ph->id);
    // right_fork = ph->id;
    while (1) {
        f = food_on_table(ph);
        if (f == 0)
            break;
        if (ph->id == 1)
            sleep (ph->sleep_seconds);//->usleep
        // grab_forks(ph, ph->id, right_fork, "right");
        toggle_mutex_forks(ph, ph->id, 1);
        put_timestamp(ph, ph->id, EATING);
        usleep (DELAY * (FOOD - f + 1));
        // down_forks(ph, right_fork);
        toggle_mutex_forks(ph, ph->id, 0);
    }
    printf ("Philosopher %zu is done eating.\n", ph->id);
    return (NULL);
}

static int food_on_table(t_philo *ph)
{
    static int food = FOOD;
    int myfood;

    pthread_mutex_lock (&ph->food_lock);
    if (food > 0) {
        food--;
    }
    myfood = food;
    pthread_mutex_unlock (&ph->food_lock);
    return myfood;
}
