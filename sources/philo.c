#include "philo.h"

void *philo(void *arg)
{
    t_params *params;

    params = (t_params *)arg;
    while(params->dead == 0 && )
    {
        check_dead();

    }

    





    
    return(0);




}



void get_forks(t_params *params)
{
    int index_left;
    int index_right;

    if(params->philos->id == params->n_philos )
    {
        index_left = 1;
        index_right = params->philos->id;
    }
    else
    {
        index_left = params->philos->id + 1;
        index_right = params->philos->id;
    }
    pthread_mutex_lock(mutex[params->philo[index_left]);
    pthread_mutex_lock(mutex[params->philo[index_right]);
    eat();
    pthread_mutex_unlock(mutex[params->philo[index_left]);
    pthread_mutex_unlock(mutex[params->philo[index_right]);
}



void eat()
{
    comprobar veces comidas
    imprimir mensaje de comer
    pasar tiempo de comer

}