#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philos
{
	int id;
	t_params *params;


}	t_philos;

typedef struct s_params
{
	int			n_philos;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_eat;
	int			dead;
	t_philos	*philos;
	
}	t_params;


// Utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void *philo(void *arg);




#endif