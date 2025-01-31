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
#ifndef FT_PHILOSOPHERS_H
# define FT_PHILOSOPHERS_H

// Standard Libraries

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

// thread
# include <pthread.h>

// gettimeofday
# include <sys/time.h>

// Errors

// 255: error of gettimeofday

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
	long		start_simulation;
	int			end_simulation;
	int			wait_start;
	int			wait_monitor;
	pthread_t	monitor;
	t_mtx		info;
	t_mtx		write;
	t_fork		*fork;
	t_philo		*philo;
}	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	id_thread;
	long		last_meal;
	int			meals_taken;
	int			full;
	t_mtx		mutex;
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

int			main(int argc, const char **argv);

// ft_philosophers.c

void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);

// ft_philosophers_2.c

void		*ft_routine(void *data);
void		*ft_monitor(void *data);
void		ft_eat(t_table *table, t_philo *philo);
void		ft_sleep(t_table *table, t_philo *philo);
void		ft_think(t_table *table, t_philo *philo);

// ft_philosophers_3.c

// ft_write.c

void		ft_write_status(t_philo *philo, t_actions action);
void		ft_write_statusd(t_philo *philo, t_actions action);

// ft_parsing.c

void		ft_init(t_table **table);
void		ft_parse(t_table *table);
void		ft_forks(t_table *table, t_philo *philo, int pos);
void		ft_init_philosophers(t_table *table);

// ft_utils.c

long		ft_gettimeofday(void);
void		ft_usleep(long msec, t_table *table);
void		ft_free(t_table *table);

// ft_utils_2.c

void		ft_wait_philosophers(t_table *table, int *wait);
int			ft_wait(t_mtx *mutex, int *wait);
int			ft_simulation_finished(t_table *table);

// ft_lib.c

void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);

#endif
