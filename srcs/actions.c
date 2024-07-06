#include "../include/philosophers.h"

void    ft_sleep(t_philo *philo, int time)
{
    pthread_mutex_lock(&philo->mustate);
	if (philo->dead != 0)
		return((void)pthread_mutex_unlock(&philo->mustate));
    pthread_mutex_unlock(&philo->mustate);
    ft_print_output(philo, 1);
    ft_msleep(time);
}

int   ft_take_fork(t_philo *philo, t_philo *first)
{
    pthread_mutex_lock(&philo->fork);
    pthread_mutex_lock(&philo->mustate);
    if (philo->dead != 0)
        return ((void)pthread_mutex_unlock(&philo->mustate), 1);
    pthread_mutex_unlock(&philo->mustate);
    ft_print_output(philo, 3);
    if (philo->next)
        pthread_mutex_lock(&philo->next->fork);
    else
    {
        pthread_mutex_lock(&first->fork);
    }
    return(0);
}

void    ft_deposit_fork(t_philo *philo, t_philo *first)
{
    pthread_mutex_unlock(&philo->fork);
    if (philo->next)
        pthread_mutex_unlock(&philo->next->fork);
    else
    {
        pthread_mutex_unlock(&first->fork);
    }
    pthread_mutex_lock(&philo->mueat);
    philo->leat = get_time();
    pthread_mutex_unlock(&philo->mueat);
}

int    ft_eat(t_philo *philo, int time, t_philo *first)
{
    pthread_mutex_lock(&philo->mustate);
	if (philo->dead != 0)
		return (pthread_mutex_unlock(&philo->mustate), 1);
    pthread_mutex_unlock(&philo->mustate);
    if(ft_take_fork(philo, first))
        return(1);
    ft_print_output(philo, 3);
    pthread_mutex_lock(&philo->mustate);
	if (philo->dead != 0)
		return (ft_deposit_fork(philo, first), pthread_mutex_unlock(&philo->mustate), 1);
    philo->state = EAT;
    pthread_mutex_unlock(&philo->mustate);
    ft_print_output(philo, 0);
    ft_msleep(time);
    ft_deposit_fork(philo, first);
	return (0);
}
