/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:48 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/27 15:02:27 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eaten(t_philos *philo)
{
	if (philo->table->n_eat == -1)
		return (1);
	if (philo->table->n_eat > philo->n_eaten)
		return (1);
	return (0);
}

int check_if_dead(t_philos *philo)
{
	int value;

	pthread_mutex_lock(&philo->table->dead);
	value = philo->table->check_dead;
	pthread_mutex_unlock(&philo->table->dead);
	// printf("---------> %d\n", value);
	return(value);
}

void	*do_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (check_if_dead(philo) == 0 && philo->table->all_eaten == 0)
	{
		do_eat(philo);
		do_print(philo, SLEEP);
		do_wait(philo, philo->table->t_sleep);
		do_print(philo, THINK);
		if (check_eaten(philo) != 1)
			break ;
	}
	return (philo);
}

void	do_threads(t_table *table)
{
	int	i;
	struct timeval time;

	i = 0;
	gettimeofday(&time, NULL);
	table->time_ref = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (i < table->n_philos)
	{
		init_philos(table, i);
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
