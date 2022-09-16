#ifndef PHILO_H
# define PHILO_H



# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;90m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define RESET "\033[0m"




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
	int			time_ref;
	int			check_dead;
	// pthread_mutex_t	dead;
	pthread_mutex_t	print;
	struct s_philos	*philos;
	
}	t_table;

typedef struct s_philos
{
	int id;
	int time;
	int n_eaten;
	pthread_t		id_thread;
	struct s_philos	*right_philo;
	pthread_mutex_t	left_f;
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
void do_threads(t_table *table);

#endif