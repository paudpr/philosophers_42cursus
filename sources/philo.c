#include "philo.h"

void	print_text(t_philos *philo, int type)
{
	if(type == 1)
		printf(YELLOW"Philo %d is eating"RESET, philo->id);
	else if (type == 2)
		printf(GREEN"Philo %d is sleeping"RESET, philo->id);
	else if(type == 3)
		printf(CYAN"Philo %d is thinking"RESET, philo->id);
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

void do_think(t_table *table)
{
	int time;

	time = get_time();
	while(table->check_dead == 0)
	{
		if(get_time() - time >= table->t_die)
			break ;
		usleep(100);
	}
}

void do_sleep(t_philos *philo)
{
	int time;

	do_print(philo, SLEEP);
	time = get_time();
	while(philo->table->check_dead == 0)
	{
		if(get_time() - time >= philo->table->t_sleep)
			break ;
		usleep(100);
	}
}


void do_eat(t_philos *philo)
{
	t_table *table;

	table = philo->table;
	// printf(CYAN"PHILO %d   %p	%p\n"RESET,philo->id, philo->table, table);
	// printf("******** TABLE %d %p %p %d\n", table->n_philos, table, table->philos, table->philos[0].id);
	pthread_mutex_lock(&philo->left_f);
	do_print(philo, FORK); //has taken a fork
	if(table->n_philos == 1)
	{
		do_think(table);
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
	pthread_mutex_unlock(&table->dead);
	do_think(table);
	philo->n_eaten++;
	pthread_mutex_unlock(&philo->left_f);
	pthread_mutex_unlock(&philo->right_philo->left_f);
}

void check_deaths(t_table *table)
{
	int i;

	if(table->n_eaten < table->n_eat)
	{
		if(table->check_dead == 0)
		{
			pthread_mutex_lock(&table->check_dead);
			if(get_time() - philo->time > philo->table->t_die)
			{
				do_print(philo, DIE);
				philo->table->check_dead = 1;
			}
			pthread_mutex_unlock(&table->check_dead);
		}
        if(table->n_eat != -1 && )
		
	}
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
		usleep(500);
	while(check_lives(philo) == 1)
	{   
		do_eat(philo);
		do_sleep(philo);
		do_print(philo, THINK);
		if(check_eaten(philo) != 1)
			break ;
	}
	return(0);
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
	check_deaths(&table);
	i = 0;
   	while(i < table->n_philos)
	{
		pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
}















// void get_forks(t_table *table)
// {
//	 int index_left;
//	 int index_right;

//	 if(table->philos->id == table->n_philos )
//	 {
//		 index_left = 1;
//		 index_right = table->philos->id;
//	 }
//	 else
//	 {
//		 index_left = table->philos->id + 1;
//		 index_right = table->philos->id;
//	 }
//	 pthread_mutex_lock(mutex[table->philo[index_left]);
//	 eat();
//	 pthread_mutex_unlock(mutex[table->philo[index_left]);
// }



// void eat()
// {
//	 comprobar veces comidas
//	 imprimir mensaje de comer
//	 pasar tiempo de comer

// }



// void	check_dead(t_table *tab)
// {
// 	int	i;

// 	while (!tab->eaten_all)
// 	{
// 		i = -1;
// 		while (!tab->dead && ++i < tab->n_philos)
// 		{
// 			pthread_mutex_lock(&tab->check);
// 			if (get_time() - tab->philos[i].last_eat > (size_t)tab->t_die)
// 			{
// 				print_msg(&tab->philos[i], MSG_RIP);
// 				tab->dead = 1;
// 			}
// 			pthread_mutex_unlock(&tab->check);
// 			usleep(100);
// 		}
// 		if (tab->dead)
// 			break ;
// 		i = 0;
// 		while (tab->n_eat != -1 && i < tab->n_philos
// 			&& tab->philos[i].eat_cnt >= tab->n_eat)
// 			i++;
// 		if (i == tab->n_philos)
// 			tab->eaten_all = 1;
// 	}
// }

// /* take forks and eat */
// static void	philo_eat(t_philo *philo)
// {
// 	t_table	*tab;

// 	tab = philo->tab;
// 	pthread_mutex_lock(&philo->fork);
// 	print_msg(philo, MSG_FORK);
// 	if (philo->tab->n_philos == 1)
// 	{
// 		hypnos(tab, tab->t_die);
// 		print_msg(philo, MSG_RIP);
// 		pthread_mutex_unlock(&philo->fork);
// 		tab->dead = 1;
// 		return ;
// 	}
// 	pthread_mutex_lock(&philo->r_philo->fork);
// 	print_msg(philo, MSG_FORK);
// 	pthread_mutex_lock(&tab->check);
// 	philo->eat_cnt++;
// 	print_msg(philo, MSG_EAT);
// 	philo->last_eat = get_time();
// 	pthread_mutex_unlock(&tab->check);
// 	hypnos(tab, tab->t_eat);
// 	pthread_mutex_unlock(&philo->fork);
// 	pthread_mutex_unlock(&philo->r_philo->fork);
// }

// /* philosophers life cicle */
// void	*philo_life(void *arg)
// {
// 	t_philo	*philo;
// 	t_table	*tab;

// 	philo = (t_philo *)arg;
// 	tab = philo->tab;
// 	if (philo->id % 2 == 0)
// 		usleep(1000);
// 	while (!tab->dead && !tab->eaten_all)
// 	{
// 		philo_eat(philo);
// 		print_msg(philo, MSG_SLP);
// 		hypnos(tab, tab->t_slp);
// 		print_msg(philo, MSG_THK);
// 	}
// 	return (NULL);
// }

// void	hypnos(t_table *tab, size_t t_slp)
// {
// 	size_t	t;

// 	t = get_time();
// 	while (!(tab->dead))
// 	{
// 		if (get_time() - t >= t_slp)
// 			break ;
// 		usleep(100);
// 	}
// }







// void	start_thread(t_philo *data)
// {
// 	int		i;

// 	i = 0;
// 	pthread_mutex_lock(data->table->start);
// 	while (i < data->table->number_of_philosophers)
// 	{
// 		pthread_create(&data[i].id_threats, NULL, \
// 			metodo_filosofo, &data[i]);
// 		i++;
// 	}
// 	data->table->time_start = ft_get_time();
// 	i = 0;
// 	while (i < data->table->number_of_philosophers)
// 	{
// 		data[i++].time_last_meal = data->table->time_start;
// 	}
// 	pthread_mutex_unlock(data->table->start);
// 	ft_usleep(1, data->table);
// 	monitor(data);
// 	i = 0;
// 	while (i < data->table->number_of_philosophers)
// 	{
// 		pthread_join(data[i].id_threats, NULL);
// 		i++;
// 	}
// }

















