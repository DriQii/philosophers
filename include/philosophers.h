#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define DEF			 "\001\e\033[0m\002"
# define RED			 "\001\e\033[0;31m\002"
# define GREEN			 "\001\e\033[0;32m\002"
# define YELLOW		 "\001\e\033[0;33m\002"
# define BLUE			 "\001\e\033[0;34m\002"
# define PURPLE		 "\001\e\033[0;35m\002"
# define CYAN			 "\001\e\033[0;36m\002"
# define WHITE			 "\001\e\033[0;37m\002"
# define BOLD_RED		 "\001\e\033[1;31m\002"
# define BOLD_GREEN	 "\001\e\033[1;32m\002"
# define BOLD_YELLOW	 "\001\e\033[1;33m\002"
# define BOLD_BLUE		 "\001\e\033[1;34m\002"
# define BOLD_PURPLE	 "\001\e\033[1;35m\002"
# define BOLD_CYAN		 "\001\e\033[1;36m\002"
# define BOLD_WHITE	 "\001\e\033[1;37m\002"
# define BOLD_BLACK	 "\001\e\033[1;30m\002"
# define COLOR			"\001\e\033[38;2;255;153;153m\002"
# define BG_GREEN		"\001\e\033[48;2;0;200;0m\002"
# define BG_RED			"\001\e\033[48;2;200;70;0m\002"
# define FG_GREEN		"\001\e\033[38;2;0;200;0m\002"
# define FG_RED			"\001\e\033[38;2;200;70;0m\002"

typedef enum    e_state
{
    THINK,
    SLEEP,
    EAT,
    DEAD,
	END,
}
               t_state;

typedef struct  s_time
{
    long long int		tdie;
    long long int		teat;
    long long int		tsleep;
	long long int		nbeat;
}               t_time;

typedef struct  s_philo
{
    int             nb;
	int				dead;
	long long int	leat;
    t_time          actime;
    t_state         state;
    pthread_t       thread;
    struct s_philo  *first;
    struct s_philo  *next;
    pthread_mutex_t *print;
    pthread_mutex_t fork;
}               t_philo;



typedef struct  s_data
{
   t_philo  *first;
   t_philo  *last;
   int      nbphilo;
}               t_data;

t_philo			*ft_create_lstphilo(int len, t_time actime);

void			*ft_routine(void *arg);
void			ft_wait_thread(t_data *data);
void			ft_create_thread(t_data *data);
void			ft_sleep(t_philo *philo, int time);
void			ft_print_output(t_philo *philo, int state);
void			*ft_routine_alive(void *arg);
void			ft_msleep(long long int time);
void	        ft_exit(t_data *data, int nb);
int			ft_eat(t_philo *philo, int time, t_philo *first);
long long int	get_time(void);

#endif
