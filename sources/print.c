#include "philo.h"

static void	print_text(t_philos *philo, int type)
{
	if (type == 1)
		printf(YELLOW"Philo %d is eating"RESET, philo->id);
	else if (type == 2)
		printf(GREEN"Philo %d is sleeping"RESET, philo->id);
	else if (type == 3)
		printf(L_BLUE"Philo %d is thinking"RESET, philo->id);
	else if (type == 4)
		printf(D_RED"Philo %d is DEAD"RESET, philo->id);
	else if (type == 5)
		printf(CYAN"Philo %d has taken a fork"RESET, philo->id);
}

void	do_print(t_philos *philo, int type)
{
	int	time;

	time = get_time() - philo->table->time_ref;
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->check_dead == 0)
	{
		printf("%d ms  ", time);
		print_text(philo, type);
		printf("\n");
	}
	pthread_mutex_unlock(&philo->table->print);
}
