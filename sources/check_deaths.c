/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_deaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:56 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/29 13:19:09 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eaten_all(t_philos *philo)
{
	int	value;

	pthread_mutex_lock(&philo->eat);
	value = philo->n_eaten;
	pthread_mutex_unlock(&philo->eat);
	return (value);
}

int	check_time(t_philos *philo)
{
	int	value;

	pthread_mutex_lock(&philo->time);
	value = philo->last_time;
	pthread_mutex_unlock(&philo->time);
	return (value);
}

static int	check_food(t_philos *philo)
{
	if (philo->table->n_eat < 0)
		return (0);
	if (check_eaten_all(philo) == philo->table->n_eat)
		return (1);
	return (0);
}

static int	check_alive(t_philos *philo)
{
	if (get_time() - check_time(philo) > philo->table->t_die)
	{
		do_print(philo, DIE);
		pthread_mutex_lock(&philo->table->dead);
		philo->table->check_dead = 1;
		pthread_mutex_unlock(&philo->table->dead);
		return (1);
	}
	return (0);
}

void	check_deaths(t_table *table)
{
	int	i;
	int	all_eaten;
	int	all_alive;

	all_eaten = 0;
	all_alive = 0;
	while (all_alive == 0 && all_eaten == 0)
	{
		i = 0;
		while (i < table->n_philos)
		{
			all_alive = check_alive(&table->philos[i]);
			all_eaten = check_food(&table->philos[i]);
			if (all_alive != 0 || all_eaten != 0)
				break ;
			i++;
		}
	}
}
