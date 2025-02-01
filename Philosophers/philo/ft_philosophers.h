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

// Standard Librairies

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

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
	int			wait_start;
	long		start_simulation;
	long		end_simulation;
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
	t_mtx		mtx;
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

int		main(void);

// ft_parsing.c

void		ft_init(t_table **table);
void		ft_parse(t_table *table);
void		ft_init_philosophers(t_table *table);

// ft_philosophers.c

void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);

// ft_routine.c

void		*ft_routine(void *data);

// ft_monitoring.c

// ft_utils.c

long		ft_gettimeofday(void);
void		ft_usleep(long msec);

// ft_lib.c

void		*ft_calloc(size_t count, size_t size);

#endif
