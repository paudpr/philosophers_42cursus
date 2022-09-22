#include "philo.h"

int ft_len_digit(int num)
{
	int len;

	len = 0;
	while(num / 10 != 0)
	{
		len++;
		num = num % 10;
	}
	return(len);
}

int check_size(char *argv)
{
	int i;
	int len;
	int num;
	char *aux;

	i = 0;
	while (argv[i] == '0' && argv[i])
		i++;
	len = ft_strlen(argv);
    if (i == len)
        return (0);
	if (len - i > 10)
		return (1);
	aux = ft_substr(argv, i, len);
	num = ft_atoi(aux);
	free(aux);
	if (num == 0 && len != ft_len_digit(num))
		return (1);
	return (0);
}

int check_digit(char *argv)
{
	int i;
    int mark;

	i = 0;
    mark = 0;
	while(argv[i])
	{
		if(ft_isdigit(argv[i]) == 0)
			mark++;
		i++;
	}
	return(mark);
}

int ckeck_args(int argc, char **argv)
{
    if(argc < 5 || argc > 6)
	{
		printf("Error: number of arguments must be between 4 and 5\n");
		exit(0);
	}
    int i = 1;
    while (i < argc)
    {
        if(check_digit(argv[i]) != 0 || check_size(argv[i]) != 0)
			return(0);
		i++;
    }
    return(1);
}


t_philos *init_philos(t_table *table)
{
	int i;
	t_philos *philos;

	philos = malloc((table->n_philos + 1) * sizeof(t_philos));
	if (philos == NULL)
		return (NULL);
	i = 0;
	while(i < table->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].time = table->time_ref;
		philos[i].n_eaten = 0;
		if(i == 0)
			philos[i].right_philo = &philos[table->n_philos - 1];
		else
			philos[i].right_philo = &philos[i - 1];
		pthread_mutex_init(&philos[i].left_f, NULL);
		philos[i].table = table;
		// printf(YELLOW"PHILO %d  %d %p    %p\n"RESET, i, philos[i].id, philos[i].table, table);
		i++;
	}
	// printf("id -> %d\n", philos[0].id);
	return (philos);
}


void init_table(t_table *table, int argc, char **argv)
{
	int i;

	if(ckeck_args(argc, argv) == 0)
	{
		printf("Error: invalid input. Must be a valid number\n");
		exit(0);
	}
	i = 0;
	table->n_philos = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->check_dead = 0;
	table->n_eat = -1;
	table->all_eaten = 0;
	if(argc == 6)
		table->n_eat = ft_atoi(argv[5]);
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->dead, NULL);
	table->philos = init_philos(table);
	// printf("--> table philo %p     %p\n", &table, table->philos);
}
