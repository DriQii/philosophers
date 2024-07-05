#include "../include/philosophers.h"

void	ft_exit(t_data *data, int nb)
{
	int     i;
    t_philo *tmp;

    i = 0;
    tmp = data->first;
    while (i++ < data->nbphilo)
    {
		if (i == nb)
			ft_print_output(tmp, 4);
        pthread_mutex_destroy(&tmp->fork);
        tmp = tmp->next;
    }
	pthread_mutex_destroy(data->first->print);
	exit(0);
}

static int	ft_check_end(t_data *data)
{
	t_philo *tmp;

	tmp = data->first;
	while(tmp)
	{
		if (tmp->state != END)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static void	ft_set_dead(t_data *data)
{
	t_philo *tmp;

	tmp = data->first;
	while(tmp)
	{
		tmp->dead = 1;
		tmp = tmp->next;
	}
}

static int	ft_check_alive(t_data *data)
{
	t_philo *tmp;

	tmp = data->first;
	while(tmp)
	{
		if((tmp->leat + tmp->actime.tdie) < get_time()
			&& tmp->state != EAT)
			{
				ft_set_dead(data);
				tmp->state = DEAD;
				return(tmp->nb);
			}
		tmp = tmp->next;
	}
	return (-1);
}

void	*ft_routine_alive(void *arg)
{
	int alive;

	usleep(1000);
	while(ft_check_end(arg))
	{
		alive = ft_check_alive(arg);
		if (alive != -1)
			ft_exit(arg, alive);
	}
	return (arg);
}
