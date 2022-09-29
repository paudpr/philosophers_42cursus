/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdel-pin <pdel-pin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:13:44 by pdel-pin          #+#    #+#             */
/*   Updated: 2022/09/29 11:16:41 by pdel-pin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define RED "\033[1;31m"
# define D_RED "\033[0;31m"
# define GREEN "\033[1;32m"
# define CYAN "\033[1;36m"
# define BLUE "\033[0;34m"
# define L_BLUE "\033[1;34m"
# define GREY "\033[1;90m"
# define YELLOW "\033[1;33m"
# define MAGENTA "\033[1;35m"
# define D_MAGENTA "\033[0;35m"
# define RESET "\033[0m"

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define FORK 5

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				all_eaten;
	long int		time_ref;
	int				check_dead;
	pthread_mutex_t	dead;
	pthread_mutex_t	print;
	struct s_philos	*philos;

}	t_table;

typedef struct s_philos
{
	int				id;
	long int		last_time;
	int				n_eaten;
	pthread_t		id_thread;
	struct s_philos	*right_philo;
	pthread_mutex_t	left_f;
	pthread_mutex_t	eat;
	pthread_mutex_t	time;
	t_table			*table;
}	t_philos;

/* Functions */
int			init_table(t_table *table, int argc, char **argv);
t_philos	*init_philos(t_table *table);
int			ckeck_args(int argc, char **argv);
void		close_philos(t_table *table);

void		do_threads(t_table *table);
void		*do_philo(void *arg);

void		do_eat(t_philos *philo);
void		do_wait(t_philos *philo, int time);
int			get_time(void);

void		check_deaths(t_table *table);
int			check_if_dead(t_philos *philo);
int			check_eaten_all(t_philos *philo);

void		do_print(t_philos *philo, int type);

char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
int			ft_atoi(const char *str);

#endif