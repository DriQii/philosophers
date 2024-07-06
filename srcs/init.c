#include "../include/philosophers.h"

static t_philo	*ft_create_philo(t_time actime, pthread_mutex_t *print, int nb)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (pthread_mutex_init(&philo->fork, NULL) != 0
		|| pthread_mutex_init(&philo->mueat, NULL) != 0
		|| pthread_mutex_init(&philo->mustate, NULL) != 0)
		return (printf("error mutex init\n"), NULL);
	philo->state = THINK;
	philo->next = NULL;
	philo->actime = actime;
	philo->print = print;
	philo->nb = nb + 1;
	philo->dead = 0;
	return (philo);
}

t_philo	*ft_create_lstphilo(int len, t_time actime, pthread_mutex_t *print)
{
	t_philo	*philo;
	t_philo	*fphilo;
	int		i;

	i = 0;
	philo = ft_create_philo(actime, print, i);
	if (!philo)
		return (NULL);
	fphilo = philo;
	while (i++ < len - 1)
	{
		philo->next = ft_create_philo(actime, print, i);
		if (!philo->next)
			return (NULL);
		philo = philo->next;
		philo->first = fphilo;
	}
	return (fphilo);
}

void	ft_wait_thread(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = data->first;
	while (i++ < data->nbphilo)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
}

void	ft_create_thread(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = data->first;
	while (i++ < data->nbphilo)
	{
		pthread_create(&tmp->thread, NULL, ft_routine, tmp);
		tmp = tmp->next;
	}
}
