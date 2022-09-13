#include "philo.h"

void *philo(void *arg)
{
    t_table *table;

    table = (t_table *)arg;
    






    return(0);
}



void do_threads(t_table *table)
{
    int i;
    pthread_t *thread;

    thread = malloc(sizeof(pthread_t) * table->n_philos);
	if(thread == NULL)
		return ;
    i = 0;
    while (i < table->n_philos)
    {
        pthread_create(&table->philos[i].id_thread, NULL, &philo, &table);
        i++;
    }
    free(thread);
}











// static void	initialise_tab(t_table *tab)
// {
// 	int	i;

// 	tab->dead = 0;
// 	tab->eaten_all = 0;
// 	tab->philos = (t_philo *)malloc(tab->n_philos * sizeof(t_philo));
// 	i = -1;
// 	while (++i < tab->n_philos)
// 	{
// 		tab->philos[i].id = i + 1;
// 		tab->philos[i].tab = tab;
// 		tab->philos[i].eat_cnt = 0;
// 		if (i + 1 == tab->n_philos)
// 			tab->philos[i].r_philo = &tab->philos[0];
// 		else
// 			tab->philos[i].r_philo = &tab->philos[i + 1];
// 		if (i == 0)
// 			tab->philos[i].l_philo = &tab->philos[tab->n_philos - 1];
// 		else
// 			tab->philos[i].l_philo = &tab->philos[i - 1];
// 		pthread_mutex_init(&tab->philos[i].fork, NULL);
// 	}
// 	pthread_mutex_init(&tab->print, NULL);
// 	pthread_mutex_init(&tab->check, NULL);
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














