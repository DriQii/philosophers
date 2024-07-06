#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	THINK,
	SLEEP,
	EAT,
	DEAD,
	END,
}					t_state;

typedef struct s_time
{
	long long int	tdie;
	long long int	teat;
	long long int	tsleep;
	long long int	nbeat;
}					t_time;

typedef struct s_philo
{
	int				nb;
	int				dead;
	long long int	leat;
	t_time			actime;
	t_state			state;
	pthread_t		thread;
	struct s_philo	*first;
	struct s_philo	*next;
	pthread_mutex_t	*print;
	pthread_mutex_t	mueat;
	pthread_mutex_t	mustate;
	pthread_mutex_t	fork;
}					t_philo;

typedef struct s_data
{
	t_philo			*first;
	t_philo			*last;
	int				nbphilo;
}					t_data;

t_philo				*ft_create_lstphilo(int len, t_time actime,
						pthread_mutex_t *print);

int					ft_eat(t_philo *philo, int time, t_philo *first);
void				*ft_routine(void *arg);
void				ft_wait_thread(t_data *data);
void				ft_create_thread(t_data *data);
void				ft_sleep(t_philo *philo, int time);
void				ft_print_output(t_philo *philo, int state);
void				*ft_routine_alive(void *arg);
void				ft_msleep(long long int time);
void				ft_exit(t_data *data);
void				ft_print_dead(t_data *data, int nb);
long long int		get_time(void);

#endif
