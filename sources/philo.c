#include "philo.h"

static int	check_eaten(t_philos *philo)
{
	if (philo->table->n_eat == -1)
		return (1);
	if (philo->table->n_eat > philo->n_eaten)
		return (1);
	return (0);
}

void	*do_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (philo->table->check_dead == 0 && philo->table->all_eaten == 0)
	{
		do_eat(philo);
		do_print(philo, SLEEP);
		do_wait(philo->table, philo->table->t_sleep);
		do_print(philo, THINK);
		if (check_eaten(philo) != 1)
			break ;
	}
	return (philo);
}

void	do_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
		pthread_create(&table->philos[i].id_thread,
			NULL, &do_philo, &table->philos[i]);
		i++;
	}
	check_deaths(table);
	i = 0;
	while (i < table->n_philos)
	{
		pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
}
