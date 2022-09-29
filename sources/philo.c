/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:48 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/29 13:17:48 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_eaten(t_philos *philo)
{
	if (philo->table->n_eat == -1)
		return (1);
	if (philo->table->n_eat > check_eaten_all(philo))
		return (1);
	return (0);
}

int	check_if_dead(t_philos *philo)
{
	int	value;

	pthread_mutex_lock(&philo->table->dead);
	value = philo->table->check_dead;
	pthread_mutex_unlock(&philo->table->dead);
	return (value);
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
		do_wait(philo, philo->table->t_sleep);
		do_print(philo, SLEEP);
		do_print(philo, THINK);
		if (check_eaten(philo) != 1)
			break ;
	}
	return (philo);
}

void	do_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philos)
	{
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
