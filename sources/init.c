#include "philo.h"

void	close_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->n_philos)
		pthread_mutex_destroy(&table->philos[i].left_f);
	pthread_mutex_destroy(&table->dead);
	pthread_mutex_destroy(&table->print);
	free(table->philos);
}

t_philos	*init_philos(t_table *table)
{
	int			i;
	t_philos	*philos;

	philos = malloc((table->n_philos + 1) * sizeof(t_philos));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < table->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].time = table->time_ref;
		philos[i].n_eaten = 0;
		if (i == 0)
			philos[i].right_philo = &philos[table->n_philos - 1];
		else
			philos[i].right_philo = &philos[i - 1];
		pthread_mutex_init(&philos[i].left_f, NULL);
		philos[i].table = table;
		i++;
	}
	return (philos);
}

int	init_table(t_table *table, int argc, char **argv)
{
	int	i;

	if (ckeck_args(argc, argv) == 0 || ft_atoi(argv[1]) == 0)
	{
		printf("Error: invalid input. Must be a valid number\n");
		return (0);
	}
	i = 0;
	table->n_philos = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->check_dead = 0;
	table->n_eat = -1;
	table->all_eaten = 0;
	if (argc == 6)
		table->n_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->dead, NULL);
	table->philos = init_philos(table);
	return (1);
}
