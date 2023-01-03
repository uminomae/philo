#include "philo.h"

static int food_on_table(t_philo *ph);
static void toggle_mutex_forks(t_philo *ph, size_t c, size_t j);

void    *dining_philosophers(void *ptr)
{
	size_t	f;
    t_philo *ph;

    ph = (t_philo *)ptr;
    printf ("Philosopher %zu is done thinking and now ready to eat.\n", ph->id);
    while (1) {
        f = food_on_table(ph);
        if (f == 0)//foodがなくなったら
            break;//プログラムの終了
        if (ph->id == 1)
            sleep (ph->sleep_seconds);//->usleep
        toggle_mutex_forks(ph, ph->id, 1);
        put_timestamp(ph, ph->id, EATING);
        usleep (DELAY * (FOOD - f + 1));
        toggle_mutex_forks(ph, ph->id, 0);
    }
    printf ("Philosopher %zu is done eating.\n", ph->id);
    return (NULL);
}

static void toggle_mutex_forks(t_philo *ph, size_t c, size_t j) {
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
