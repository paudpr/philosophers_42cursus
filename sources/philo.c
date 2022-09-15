#include "philo.h"

void *philo(void *arg)
{
    t_table *table;
    int i;

    table = (t_table *)arg;
    i = -1;
    while(++i < table->n_philos)
        if(table->philos[i].id % 2 == 0)
            usleep(500);

    if(table->philos)
    // printf("TABLE %d %p %p %d\n", table->n_philos, table, table->philos, table->philos[1].id);
    // printf("%d\n", table->philos->id);
    while(1)
    {
        if(table->philos[0].id == 1)
            printf(RED"soy filosofo 1\n"RESET);
        if(table->philos[1].id == 2)
            printf(CYAN"soy filosofo 2\n"RESET);
        if(table->philos[2].id == 3)
            printf(YELLOW"soy filosofo 3\n"RESET);
        if(table->philos[3].id == 4)
            printf(GREEN"soy filosofo 4\n"RESET);
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
        pthread_create(&table->philos[i].id_thread, NULL, &philo, table);
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














