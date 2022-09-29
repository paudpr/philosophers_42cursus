/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:52 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/29 13:18:36 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	useconds_t		current_time;
	struct timeval	start;

	gettimeofday(&start, NULL);
	current_time = (start.tv_sec) * 1000 + (start.tv_usec) / 1000;
	return (current_time);
}

void	do_wait(t_philos *philo, int time)
{
	int	time_now;

	time_now = get_time();
	while (check_if_dead(philo) == 0)
	{
		if (get_time() - time_now >= time)
			break ;
		usleep(500);
	}
}

static int	do_one_philo(t_philos *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->n_philos == 1)
	{
		do_wait(philo, philo->table->t_die);
		do_print(philo, DIE);
		pthread_mutex_unlock(&philo->left_f);
		pthread_mutex_lock(&table->dead);
		table->check_dead = 1;
		pthread_mutex_unlock(&table->dead);
		return (1);
	}
	return (0);
}

void	do_eat(t_philos *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->left_f);
	do_print(philo, FORK);
	if (do_one_philo(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->right_philo->left_f);
	do_print(philo, FORK);
	do_print(philo, EAT);
	pthread_mutex_lock(&philo->time);
	philo->last_time = get_time();
	pthread_mutex_unlock(&philo->time);
	pthread_mutex_lock(&philo->eat);
	philo->n_eaten++;
	pthread_mutex_unlock(&philo->eat);
	do_wait(philo, philo->table->t_eat);
	pthread_mutex_unlock(&philo->left_f);
	pthread_mutex_unlock(&philo->right_philo->left_f);
}
