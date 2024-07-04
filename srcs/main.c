#include "../include/philosophers.h"

void    *ft_routine(void *arg)
{
    t_philo *philo;
    int i = 0;

    while (i++ < 2)
    {
        philo = (t_philo *)arg;
        if (i == 1)
            ft_print_output(philo, 2);
        ft_eat(philo, philo->actime.teat, philo->first);
        ft_sleep(philo, philo->actime.tsleep);
        ft_print_output(philo, 2);
    }
    return(arg);
}

int main(int argc, char **argv)
{
    t_data  data;
    t_time  actime;

    if (argc < 5 || argc > 6)
        return (1);
    actime.tdie = ft_atoi(argv[2]);
    actime.teat = ft_atoi(argv[3]);
    actime.tsleep = ft_atoi(argv[4]);
    data.nbphilo = ft_atoi(argv[1]);
    data.first = ft_create_lstphilo(data.nbphilo, actime);
    ft_create_thread(&data);
    ft_wait_thread(&data);
}



/* pthread_mutex_t mutex;
int count;

void    *ft_test(void *arg)
{
    pthread_mutex_lock(&mutex);
    while(count != 10)
        printf("%d\n", count++);
    count = 0;
    printf("%s\n", (char *)arg);
    pthread_mutex_unlock(&mutex);
    return(arg);
}

int main(int argc, char **argv)
{
    (void)argc;
    pthread_t t1[10];
    int i = 0;
    pthread_mutex_init(&mutex, NULL);
    while (++i < argc)
        pthread_create(&t1[i], NULL, ft_test, argv[i]);
    i = -1;
    while (++i < argc)
        pthread_join(t1[i], NULL);
} */