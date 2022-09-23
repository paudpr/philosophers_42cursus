#include "philo.h"

static int	ft_len_digit(int num)
{
	int	len;

	len = 0;
	while (num / 10 != 0)
	{
		len++;
		num = num % 10;
	}
	return (len);
}

static int	check_size(char *argv)
{
	int		i;
	int		len;
	int		num;
	char	*aux;

	i = 0;
	while (argv[i] == '0' && argv[i])
		i++;
	len = ft_strlen(argv);
	if (i == len)
		return (0);
	if (len - i > 10)
		return (1);
	aux = ft_substr(argv, i, len);
	num = ft_atoi(aux);
	free(aux);
	if (num == 0 && len != ft_len_digit(num))
		return (1);
	return (0);
}

static int	check_digit(char *argv)
{
	int	i;
	int	mark;

	i = 0;
	mark = 0;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]) == 0)
			mark++;
		i++;
	}
	return (mark);
}

int	ckeck_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Error: number of arguments must be between 4 and 5\n");
		exit(0);
	}
	i = 1;
	while (i < argc)
	{
		if (check_digit(argv[i]) != 0 || check_size(argv[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}
