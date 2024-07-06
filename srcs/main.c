#include "../include/philosophers.h"


void    *ft_routine(void *arg)
{
    t_philo *philo;
    int i = 0;

	philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->mueat);
	philo->leat = get_time();
    pthread_mutex_unlock(&philo->mueat);
	ft_print_output(philo, 2);
	if (philo->nb % 2 != 0)
		ft_msleep(philo->actime.teat / 3);
    while (i < philo->actime.nbeat || philo->actime.nbeat == -1)
    {
        if (ft_eat(philo, philo->actime.teat, philo->first) == 1)
            break;
		if (i + 1 != philo->actime.nbeat)
        	ft_sleep(philo, philo->actime.tsleep);
        ft_print_output(philo, 2);
		i++;
    }
    pthread_mutex_lock(&philo->mustate);
	philo->state = END;
    pthread_mutex_unlock(&philo->mustate);
    return(arg);
}

int ft_check_arg(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    j = 0;
    while(i < argc)
    {
        while(argv[i][j])
        {
            if(argv[i][j] < '0' || argv[i][j] > '9')
            {
                printf("Use only numeric character\n");
                printf("ARGS :\n[number_of_philosophers]\n[time_to_");
                printf("die]\n[time_to_eat]\n[time_to_sleep]\n\nOPTIONAL:\n");
                printf("[number_of_times_each_philosopher_must_eat]\n");
                return (1);
            }
            j++;
        }
        i++;
        j = 0;
    }
    return(0);
}

int main(int argc, char **argv)
{
    t_data		    data;
    t_time		    actime;
	pthread_t	    alive;
    pthread_mutex_t print;

    if (argc < 5 || argc > 6 || ft_check_arg(argc, argv))
        return (1);
	else if (argc == 6)
		actime.nbeat = ft_atoi(argv[5]);
	else
		actime.nbeat = -1;
    pthread_mutex_init(&print, NULL);
    actime.tdie = ft_atoll(argv[2]);
    actime.teat = ft_atoll(argv[3]);
    actime.tsleep = ft_atoll(argv[4]);
    data.nbphilo = ft_atoi(argv[1]);
    data.first = ft_create_lstphilo(data.nbphilo, actime, &print);
	if (!data.first)
		return (1);
    ft_create_thread(&data);
    pthread_create(&alive, NULL, ft_routine_alive, &data);
    ft_wait_thread(&data);
    pthread_join(alive, NULL);
    ft_exit(&data);
}
