#include "philo.h"

void *philo(void *arg)
{
    t_table *table;

    table = (t_table *)arg;
    






    return(0);
}








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
//     pthread_mutex_lock(mutex[table->philo[index_right]);
//     eat();
//     pthread_mutex_unlock(mutex[table->philo[index_left]);
//     pthread_mutex_unlock(mutex[table->philo[index_right]);
// }



// void eat()
// {
//     comprobar veces comidas
//     imprimir mensaje de comer
//     pasar tiempo de comer

// }