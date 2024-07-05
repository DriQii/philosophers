#include "../include/philosophers.h"

void    *ft_routine(void *arg)
{
    t_philo *philo;
    int i = 0;

	philo = (t_philo *)arg;
	philo->leat = get_time();
	ft_print_output(philo, 2);
	if (philo->nb % 2 != 0)
		ft_msleep(philo->actime.teat / 3);
    while (i < philo->actime.nbeat || philo->actime.nbeat == -1)
    {
        if (philo->dead != 0
			|| ft_eat(philo, philo->actime.teat, philo->first) == 1)
				break;
		if (i + 1 != philo->actime.nbeat)
        	ft_sleep(philo, philo->actime.tsleep);
        ft_print_output(philo, 2);
		i++;
    }
	philo->state = END;
    return(arg);
}



int main(int argc, char **argv)
{
    t_data		data;
    t_time		actime;
	pthread_t	alive;

    if (argc < 5 || argc > 6)
        return (1);
    actime.tdie = ft_atoll(argv[2]);
    actime.teat = ft_atoll(argv[3]);
    actime.tsleep = ft_atoll(argv[4]);
	if (argc == 6)
		actime.nbeat = ft_atoi(argv[5]);
	else
		actime.nbeat = -1;
    data.nbphilo = ft_atoi(argv[1]);
    data.first = ft_create_lstphilo(data.nbphilo, actime);
    ft_create_thread(&data);
	pthread_create(&alive, NULL, ft_routine_alive, &data);
	pthread_join(alive, NULL);
    ft_wait_thread(&data);
}
