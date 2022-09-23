#include "philo.h"

int	main(int argc, char **argv)
{
	t_table			table;
	struct timeval	time;

	gettimeofday(&time, NULL);
	table.time_ref = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (init_table(&table, argc, argv) == 1)
	{
		do_threads(&table);
		close_philos(&table);
	}
	return (0);
}
