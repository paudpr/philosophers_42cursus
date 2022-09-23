#include "philo.h"

int	get_time(void)
{
	useconds_t		current_time;
	struct timeval	start;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
	return (current_time);
}

void	do_wait(t_table *table, int time)
{
	int	time_now;

	time_now = get_time();
	while (table->check_dead == 0)
	{
		if (get_time() - time_now >= time)
			break ;
		usleep(100);
	}
}

void	do_eat(t_philos *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->left_f);
	do_print(philo, FORK);
	if (table->n_philos == 1)
	{
		do_wait(table, philo->table->t_die);
		do_print(philo, DIE);
		pthread_mutex_unlock(&philo->left_f);
		table->check_dead = 1;
		return ;
	}
	pthread_mutex_lock(&philo->right_philo->left_f);
	do_print(philo, FORK);
	pthread_mutex_lock(&table->dead);
	do_print(philo, EAT);
	philo->time = get_time();
	philo->n_eaten++;
	pthread_mutex_unlock(&table->dead);
	do_wait(table, philo->table->t_eat);
	pthread_mutex_unlock(&philo->left_f);
	pthread_mutex_unlock(&philo->right_philo->left_f);
}
