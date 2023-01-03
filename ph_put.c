#include "philo.h"


void    put_taken_fork(size_t id)
{
    printf("%zu", id);
    printf(TAKEN_FORK_STR);
    printf(NL);
}

void    put_eating(size_t id)
{
    printf("%zu", id);
    printf(EATING_STR);
    printf(NL);
}

void    put_sleeping(size_t id)
{
    printf("%zu", id);
    printf(SLEEPING_STR);
    printf(NL);
}

void    put_thinking(size_t id)
{
    printf("%zu", id);
    printf(THINKING_STR);
    printf(NL);
}

void    put_died(size_t id)
{
    printf("%zu", id);
    printf(DIED_STR);
    printf(NL);
}
