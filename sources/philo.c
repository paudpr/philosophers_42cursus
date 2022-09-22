#include "philo.h"

void	print_text(t_philos *philo, int type)
{
	if(type == 1)
		printf(YELLOW"Philo %d is eating"RESET, philo->id);
	else if (type == 2)
		printf(GREEN"Philo %d is sleeping"RESET, philo->id);
	else if(type == 3)
		printf(BLUE"Philo %d is thinking"RESET, philo->id);
	else if(type == 4)
		printf(RED"Philo %d is DEAD"RESET, philo->id);
	else if(type == 5)
		printf(CYAN"Philo %d has taken a fork"RESET, philo->id);
}

void	do_print(t_philos *philo, int type)
{
	int time;

	time = get_time() - philo->table->time_ref;
	pthread_mutex_lock(&philo->table->print);
	if(philo->table->check_dead == 0)
	{
		printf("%d ms  ", time);
		print_text(philo, type);
		printf("\n");
	}
	pthread_mutex_unlock(&philo->table->print);
}

int	get_time(void)
{
	useconds_t		current_time;
	struct timeval	start;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
	return (current_time);
}

void do_wait(t_table *table, int time)
{
	int time_now;

	time_now = get_time();
	while(table->check_dead == 0)
	{
		if(get_time() - time_now >= time)
			break ;
		usleep(100);
	}
}

void do_eat(t_philos *philo)
{
	t_table *table;

	table = philo->table;
	pthread_mutex_lock(&philo->left_f);
	do_print(philo, FORK);
	if(table->n_philos == 1)
	{
		do_wait(table, philo->table->t_die);
		do_print(philo, DIE);
		pthread_mutex_unlock(&philo->left_f);
		table->check_dead = 1;
		printf("TERmino bucle 1 philo\n");
		return ;
	}
	pthread_mutex_lock(&philo->right_philo->left_f);
	do_print(philo, FORK);
	pthread_mutex_lock(&table->dead);
	printf("philo %d -> %d         %d\n", philo->id, philo->time - get_time(), philo->n_eaten);
	do_print(philo, EAT);
	philo->time = get_time();
	philo->n_eaten++;
	pthread_mutex_unlock(&table->dead);
	do_wait(table, philo->table->t_eat);
	pthread_mutex_unlock(&philo->left_f);
	pthread_mutex_unlock(&philo->right_philo->left_f);
}

static int check_food(t_philos *philo)
{
	if(philo->table->n_eat < 0)
		return(0);
	if(philo->n_eaten == philo->table->n_eat)
		return(1);
	return(0);
}

static int check_alive(t_philos *philo)
{
	pthread_mutex_lock(&philo->table->dead);
	if(get_time() - philo->time > philo->table->t_die)
	{
		// philo->table->check_dead = 1;
		pthread_mutex_unlock(&philo->table->dead);
		return(1);
	}
	pthread_mutex_unlock(&philo->table->dead);
	return(0);
}

void check_deaths(t_table *table)
{
	int i;
	int all_eaten;
	int all_alive;

	all_eaten = 0;
	all_alive = 0;
	fprintf(stderr, "Aqui entra perra");
	while(all_alive == 0 && all_eaten == 0)
	{
		i = 0;
		while(i < table->n_philos)
		{
			all_alive = check_alive(&table->philos[i]);
			all_eaten = check_food(&table->philos[i]);
			if(all_alive != 0 || all_eaten != 0)
				break ;
			i++;
		}
	}
	if(all_alive != 0)
		do_print(&table->philos[i], DIE);
}

static int check_eaten(t_philos *philo)
{
	if(philo->table->n_eat == -1)
		return(1);
	if(philo->table->n_eat > philo->n_eaten)
		return(1);
	return(0);
}

static int check_lives(t_philos *philo)
{
	pthread_mutex_lock(&philo->table->dead);
	if(philo->table->check_dead == 0)
	{
		pthread_mutex_unlock(&philo->table->dead);
		return (1);
	}
	return (0);
}

void *do_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if(philo->id % 2 == 0)
		usleep(100);
	while(check_lives(philo) == 1)
	{   
		do_eat(philo);
		do_print(philo, SLEEP);
		do_wait(philo->table, philo->table->t_sleep);
		do_print(philo, THINK);
		if(check_eaten(philo) != 1)
			break ;
	}
	printf("termino funcion do_philo\n");
	return(philo);
}

void do_threads(t_table *table)
{
	int i;

	i = 0;
	// printf("ORIGINAL TABLE %d %p %p %d\n", table->n_philos, table, table->philos, table->philos[0].id);
	while (i < table->n_philos)
	{
		pthread_create(&table->philos[i].id_thread, NULL, &do_philo, &table->philos[i]);
		i++;
	}
	printf("termino bucle do_threads\n");
	check_deaths(table);
	i = 0;
	printf("despues de comprobar muertes\n");
   	while(i < table->n_philos)
	{
		pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
	printf("termino bucle do_joins\n");
}
