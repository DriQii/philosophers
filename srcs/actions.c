#include "../include/philosophers.h"

void    ft_print_output(t_philo *philo, int state)
{
	char			*str;
    long long int	time;

	str = NULL;
    time = get_time();
    if (state == 0)
        str = ft_strdup("is eating");
    else if (state == 1)
        str = ft_strdup("is sleeping");
    else if (state == 2)
        str = ft_strdup("is thinking");
    else if (state == 3)
        str = ft_strdup("has taken a fork");
    //pthread_mutex_lock(philo->print);
	printf("%lld %d %s\n", time, (int)philo->nb, str);
    //pthread_mutex_unlock(philo->print);
}

void    ft_sleep(t_philo *philo, int time)
{
    ft_print_output(philo, 1);
    philo->state = SLEEP;
    ft_usleep(time);
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
    ft_usleep(time);
    pthread_mutex_unlock(&philo->fork);
    if (philo->next)
        pthread_mutex_unlock(&philo->next->fork);
    else
        pthread_mutex_unlock(&first->fork);
}
