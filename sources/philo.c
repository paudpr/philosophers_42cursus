#include "philo.h"

void do_eat(t_philos *philo)
{
    t_table *table;


    table = philo->table;
    pthread_mutex_lock(&philo->left_f);
    ////printear mensaje de coger tenedor

    pthread_mutex_lock(&philo->right_philo->left_f);
    //// printear mensaje de coger otro tenedor
    philo->n_eaten++;
    ///printear mensaje de comer

    ////comprobar que no están muertos?????

    ///registrar paso del tiempo

    pthread_mutex_unlock(&philo->left_f);
    pthread_mutex_unlock(&philo->right_philo->left_f);
}





void *philo(void *arg)
{
    t_philos    *philo;
    int i; 

    philo = (t_philos *)arg;
    if(philo->id % 2 == 0)
        usleep(500);

    // printf("TABLE %d %p %p %d\n", table->n_philos, table, table->philos, table->philos[1].id);
    // printf("%d\n", table->philos->id);
    i = 0;
    while(1)
    {   
        do_eat(&philo[philo->id - 1]);
        do_sleep(philo->table);
    
    }

    return(0);

}



void do_threads(t_table *table)
{
    int i;

    i = 0;
	// printf(" ORIGINAL TABLE %d %p %p %d\n", table->n_philos, table, table->philos, table->philos[1].id);
    while (i < table->n_philos)
    {
        pthread_create(&table->philos[i].id_thread, NULL, &philo, &table->philos[i]);
        i++;
    }
    i = 0;
   	while(i < table->n_philos)
	{
        // printf("%d\n", i);
		pthread_join(table->philos[i].id_thread, NULL);
		i++;
	}
}








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





// void get_forks(t_table *table)
// {
//     int index_left;
//     int index_right;

//     if(table->philos->id == table->n_philos )
//     {
//         index_left = 1;
//         index_right = table->philos->id;
//     }
//     else
//     {
//         index_left = table->philos->id + 1;
//         index_right = table->philos->id;
//     }
//     pthread_mutex_lock(mutex[table->philo[index_left]);
//     eat();
//     pthread_mutex_unlock(mutex[table->philo[index_left]);
// }



// void eat()
// {
//     comprobar veces comidas
//     imprimir mensaje de comer
//     pasar tiempo de comer

// }














