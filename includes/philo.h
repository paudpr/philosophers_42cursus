#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>


typedef struct s_table
{
	int			n_philos;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_eat;
	int			dead;
	int			time_ref;
	
	struct s_philos	*philos;
	
}	t_table;

typedef struct s_philos
{
	int id;

	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	t_table *table;


}	t_philos;

// Utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);

void *philo(void *arg);
void init_table(t_table *table, int argc, char **argv);
int ckeck_args(int argc, char **argv);
int check_digit(char *argv);
int check_size(char *argv);

#endif