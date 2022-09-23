/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_deaths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:56 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/23 16:13:57 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_food(t_philos *philo)
{
	if (philo->table->n_eat < 0)
		return (0);
	if (philo->n_eaten == philo->table->n_eat)
		return (1);
	return (0);
}

static int	check_alive(t_philos *philo)
{
	pthread_mutex_lock(&philo->table->dead);
	if (get_time() - philo->time > philo->table->t_die)
	{
		do_print(philo, DIE);
		philo->table->check_dead = 1;
		pthread_mutex_unlock(&philo->table->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->dead);
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
