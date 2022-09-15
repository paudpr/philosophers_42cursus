#include "philo.h"







useconds_t	ft_get_time(void)
{
	useconds_t		current_time;
	struct timeval	start;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
	return (current_time);
}

useconds_t	time_diff(useconds_t present, useconds_t past)
{
	return (present - past);
}

void	ft_usleep(useconds_t time, t_table *table)
{
	useconds_t	start;
	useconds_t	mytime;

	start = ft_get_time();
	mytime = ft_get_time();
	pthread_mutex_lock(table->live);
	while ((mytime - start) < time && table->alive)
	{
		pthread_mutex_unlock(table->live);
		usleep(500);
		mytime = ft_get_time();
		pthread_mutex_lock(table->live);
	}
	pthread_mutex_unlock(table->live);
}

