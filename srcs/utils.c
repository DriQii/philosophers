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
