#include "../include/philosophers.h"

static t_philo *ft_create_philo(t_time actime, pthread_mutex_t *print, int nb)
{
    t_philo *philo;

    philo = malloc(sizeof(*philo));
    pthread_mutex_init(&philo->fork, NULL);
    philo->state = THINK;
    philo->next = NULL;
    philo->actime = actime;
    philo->print = print;
    philo->nb = nb + 1;
    return (philo);
}

t_philo *ft_create_lstphilo(int len, t_time actime)
{
    t_philo *philo;
    t_philo *fphilo;
    pthread_mutex_t print;
    int     i;

    i = 0;
    pthread_mutex_init(&print, NULL);
    philo = ft_create_philo(actime, &print, i);
    fphilo = philo;
    while(i++ < len)
    {
        philo->next = ft_create_philo(actime, &print, i);
        philo = philo->next;
        philo->first = fphilo;
    }
    return(fphilo);
}

void    ft_wait_thread(t_data *data)
{
    int     i;
    t_philo *tmp;

    i = 0;
    tmp = data->first;
    while (i++ < data->nbphilo)
    {
        pthread_join(tmp->thread, NULL);
        tmp = tmp->next;
    }
}

void    ft_create_thread(t_data *data)
{
    int     i;
    t_philo *tmp;

    i = 0;
    tmp = data->first;
    while (i++ < data->nbphilo)
    {
        pthread_create(&tmp->thread, NULL, ft_routine, tmp);
        tmp = tmp->next;
    }

}