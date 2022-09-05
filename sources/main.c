#include "philo.h"

int ft_len_digit(int num)
{
	int len;

	len = 0;
	while(num / 10 != 0)
	{
		len++;
		num = num % 10;
	}
	return(len);
}

int check_size(char *argv)
{
	int i;
	int len;
	int num;
	char *aux;

	i = 0;
	while(argv[i] == '0' && argv[i])
		i++;
	len = ft_strlen(argv) - i;
	if(len > 10)
		return(1);
	aux = ft_substr(argv, i, len);
	num = ft_atoi(aux);
	free(aux);
	if(num == 0 || len != ft_len_digit(num))
		return(1);
	return(0);
}

int check_digit(char *argv)
{
	int i;

	i = 0;
	while(argv[i])
	{
		if(ft_isdigit(argv[i]) != 0)
			return(1);
		i++;
	}
	return(0);
}

int check_valid(int argc, char **argv)
{
	int i;

	i = 1;
	while(i < argc)
	{
		if(check_digit(argv[i]) == 0 || check_size(argv[i]) == 0)
			return(0);
		i++;
	}
	return(1);
}

void init_params(t_params *params, int argc, char **argv)
{
	int i;

	i = 0;
	if(check_valid(argc, argv) == 0)
	{
		printf("Error: invalid input. Must be a number\n");
		exit(0);
	}
	(void)params;
	// params->n_philos = ft_atoi(argv[1]);
	// params->t_die = ft_atoi(argv[2]);
	// params->t_eat = ft_atoi(argv[3]);
	// params->t_sleep = ft_atoi(argv[4]);
	// if(argc == 6)
	// 	params->n_eat = ft_atoi(argv[5]);
	// else
	// 	params->n_eat = -1;
}


void *print_hello(void *num)
{
	printf("HELLO NUM %d\n", *((int *)num));
	printf("\n");
	return (0);
}

void init_threads(pthread_t *thread, t_params *params)
{
	int i;

	i = 0;
	while(i < params->n_philos)
	{
		pthread_create(&thread[i], NULL, &print_hello, &params->philos[i].id);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_params params;
	pthread_t *thread;
	int start_time;
	struct timeval time;
	int num; 

	// if(argc < 5 || argc > 6)
	// {
	// 	printf("Error: number of arguments must be between 4 and 5\n");
	// 	exit(0);
	// }
	init_params(&params, argc, argv);
	thread = malloc(sizeof(pthread_t) * params.n_philos);
	if(thread == NULL)
		return (0);

	gettimeofday(&time, NULL);
	start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);


	num = 0;
	init_threads(thread, &params);
	// while(1)
	// {
	// 	philos_living();
	// }
	

	free(thread);
	system("leaks -q philo");
	return (0);
}
