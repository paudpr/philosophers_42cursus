/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:28 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/29 13:17:57 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table			table;
	struct timeval	time;

	gettimeofday(&time, NULL);
	table.time_ref = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	if (init_table(&table, argc, argv) == 1)
	{
		do_threads(&table);
		close_philos(&table);
	}
	return (0);
}
