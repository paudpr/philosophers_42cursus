#include "philo.h"


void *print_hello(void *num)
{
	t_philos	*cast = (t_philos *)num;
	printf("HELLO NUM %d   %p\n", cast->id, cast);
	printf("\n");
	return (0);
}

void prueba_threads(pthread_t *thread, t_table *table)
{
	int i;

	i = 0;
	while(i < table->n_philos)
	{
		table->philos[i].id = i + 1;
		pthread_create(&thread[i], NULL, &print_hello, &table);
		// printf("%d   %p\n", table->n_philos, table);
		// pthread_detach(thread[table->n_philos]);
		i++;
	}


	// i = 0;
	// while( i < table->n_philos)
	// {
	// 	pthread_join(thread[i], NULL);
	// 	i++;
	// }
}

int main(int argc, char **argv)
{
	t_table table;
	struct timeval time;

	gettimeofday(&time, NULL);
	table.time_ref = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	init_table(&table, argc, argv);


	do_threads(&table);
	// prueba_threads(thread, &table);
	// system("leaks -q philo");
	return (0);
}
