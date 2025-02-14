/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   • Résoud le dîner des philosophes.                                       */
/*   • ./philo [ nb_hilo ] [ die ] [ eat ] [ sleep ] ([ max_meals ])          */
/*      -> nb_philo  - number_of_philosophers                                 */
/*      -> die       - time_to_die                                 [ in ms ]  */
/*      -> eat       - time_to_eat                                 [ in ms ]  */
/*      -> sleep     - time_to_sleep                               [ in ms ]  */
/*      -> max_meals - number_of_times_each_philosopher_must_eat              */
/* ************************************************************************** */
#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

// Standard Librairies

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// thread
# include <pthread.h>

// gettimeofday
# include <sys/time.h>

// Structures

typedef pthread_mutex_t		t_mtx;
typedef struct s_table		t_table;
typedef struct s_philo		t_philo;
typedef struct s_fork		t_fork;

typedef struct s_table
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			max_meals;
	int			full;
	int			end_simulation;
	long		start_simulation;
	pthread_t	monitor;
	t_mtx		info;
	t_mtx		write;
	t_mtx		replete;
	t_fork		*fork;
	t_philo		*philo;
}	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	id_thread;
	long		last_meal;
	t_mtx		time;
	t_fork		*left_fork;
	t_fork		*right_fork;
	t_table		*table;
}	t_philo;

typedef struct s_fork
{
	int			id;
	t_mtx		fork;
}	t_fork;

// Enum

typedef enum e_actions
{
	LEFT_FORK,
	RIGHT_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_actions;

//	---------- MY CODE ----------

// main.c

int			main(int argc, char **argv);

// ft_parsing.c

int			ft_init(t_table **table, char **argv);
int			ft_parse(t_table *table, char **argv, int i);
void		ft_init_philosophers(t_table *table);

// ft_philosophers.c

void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);

// ft_routine.c

void		*ft_routine(void *data);
int			ft_eat(t_philo *philo, int *max_meals, int *flg);
int			ft_avoid_deadlock(t_philo *philo,
				int *max_meals, int *flg);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);

// ft_monitoring.c

void		*ft_monitor(void *data);
void		ft_philo_died(t_table *table, int id);

// ft_check.c

int			ft_check_death(t_philo *philo);
int			ft_check_last_meal(t_philo *philo);
int			ft_check_replete(t_philo *philo);
int			ft_check_atoi(const char *s, int sign);
int			ft_check_int_min(const char *s);

// ft_utils.c

long		ft_gettimeofday(void);
void		ft_usleep(long ms);
void		ft_usleep_max_meals(long ms, t_philo *philo,
				int *max_meals, int *flg);
void		ft_write(t_philo *philo, t_actions action);
void		ft_i_am_replete(t_philo *philo);

// ft_lib.c

int			ft_atoi(const char *s);
void		*ft_calloc(size_t count, size_t size);
void		ft_putstr_fd(char *s, int fd);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
