#include "../include/philosophers.h"

void    ft_think(t_philo *philo, int time)
{
    philo->state = THINK;
    usleep(time);
}
void    ft_print_output(t_philo *philo, int state)
{
    struct timeval actime;
    gettimeofday(&actime, NULL);
    pthread_mutex_lock(philo->print);
    if (state == 0)
        printf("%lld %d is eating\n", (long long int)actime.tv_usec, (int)philo->nb);
    else if (state == 1)
        printf("%lld %d is sleeping\n", (long long int)actime.tv_usec, (int)philo->nb);
    else if (state == 2)
        printf("%lld %d is thinking\n", (long long int)actime.tv_usec, (int)philo->nb);
    else if (state == 3)
        printf("%lld %d has taken a fork\n", (long long int)actime.tv_usec, (int)philo->nb);
    pthread_mutex_unlock(philo->print);
}

void    ft_sleep(t_philo *philo, int time)
{
    ft_print_output(philo, 1);
    philo->state = SLEEP;
    usleep(time);
}

void    ft_eat(t_philo *philo, int time, t_philo *first)
{

    pthread_mutex_lock(&philo->fork);
    ft_print_output(philo, 3);
    if (philo->next)
        pthread_mutex_lock(&philo->next->fork);
    else
        pthread_mutex_lock(&first->fork);
    ft_print_output(philo, 3);
    ft_print_output(philo, 0);
    philo->state = EAT;
    usleep(time);
    pthread_mutex_unlock(&philo->fork);
    if (philo->next)
        pthread_mutex_unlock(&philo->next->fork);
    else
        pthread_mutex_unlock(&first->fork);
}
