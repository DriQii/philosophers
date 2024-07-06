/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alive.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evella <evella@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 21:12:43 by evella            #+#    #+#             */
/*   Updated: 2024/07/06 21:12:44 by evella           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static int	ft_check_end(t_data *data)
{
	t_philo	*tmp;

	tmp = data->first;
	while (tmp)
	{
		pthread_mutex_lock(&tmp->mustate);
		if (tmp->state != END)
			return (pthread_mutex_unlock(&tmp->mustate), 1);
		pthread_mutex_unlock(&tmp->mustate);
		tmp = tmp->next;
	}
	return (0);
}

static void	ft_set_dead(t_data *data)
{
	t_philo	*tmp;

	tmp = data->first;
	while (tmp)
	{
		pthread_mutex_lock(&tmp->mustate);
		tmp->dead = 1;
		pthread_mutex_unlock(&tmp->mustate);
		tmp = tmp->next;
	}
}

static int	ft_check_alive(t_data *data)
{
	t_philo			*tmp;
	long long int	eattime;

	tmp = data->first;
	while (tmp)
	{
		pthread_mutex_lock(&tmp->mueat);
		eattime = tmp->leat + tmp->actime.tdie;
		pthread_mutex_unlock(&tmp->mueat);
		pthread_mutex_lock(&tmp->mustate);
		if ((eattime) < get_time() && tmp->state != EAT)
		{
			pthread_mutex_unlock(&tmp->mustate);
			ft_set_dead(data);
			pthread_mutex_lock(&tmp->mustate);
			tmp->state = DEAD;
			pthread_mutex_unlock(&tmp->mustate);
			return (tmp->nb);
		}
		pthread_mutex_unlock(&tmp->mustate);
		tmp = tmp->next;
	}
	return (-1);
}

void	*ft_routine_alive(void *arg)
{
	int	alive;

	usleep(1000);
	while (ft_check_end(arg))
	{
		alive = ft_check_alive(arg);
		if (alive != -1)
		{
			ft_print_dead(arg, alive);
			break ;
		}
	}
	return (arg);
}
