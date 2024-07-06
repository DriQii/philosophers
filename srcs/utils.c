/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:12:48 by evella            #+#    #+#             */
/*   Updated: 2024/07/06 21:12:49 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long long int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void	ft_msleep(long long int time)
{
	usleep(time * 1000);
}
void	ft_print_dead(t_data *data, int nb)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = data->first;
	while (i++ < data->nbphilo)
	{
		if (i == nb)
			ft_print_output(tmp, 4);
	}
}

void	ft_exit(t_data *data)
{
	int		i;
	t_philo	*tmp;
	t_philo	*tmp2;

	i = 0;
	tmp = data->first;
	while (i++ < data->nbphilo)
	{
		pthread_mutex_lock(&tmp->mustate);
		while (tmp->state != END && tmp->state != DEAD)
		{
			usleep(1000);
			pthread_mutex_unlock(&tmp->mustate);
			usleep(1000);
			pthread_mutex_lock(&tmp->mustate);
			usleep(1000);
		}
		if (i == 1)
			pthread_mutex_destroy(tmp->print);
		pthread_mutex_unlock(&tmp->mustate);
		pthread_mutex_destroy(&tmp->fork);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}

void	ft_print_output(t_philo *philo, int state)
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
	else if (state == 4)
	{
		str = ft_strdup("died");
		usleep(200000);
	}
	pthread_mutex_lock(philo->print);
	printf("%lld %d %s\n", time, (int)philo->nb, str);
	pthread_mutex_unlock(philo->print);
	free(str);
}
