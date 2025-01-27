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
#include <sys/time.h>

// Structures

typedef pthread_mutex_t	t_mtx;
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
	int			a;
	t_philo		*philo;
	t_fork		*fork;
	t_mtx		info;
}	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	id_thread;
	t_fork		*left;
	t_fork		*right;
	t_table		*table;
}	t_philo;

typedef struct s_fork
{
	int			id;
	t_mtx		fork;
}	t_fork;

//	---------- MY CODE ----------

// ft_philosophers.c

// ft_philosophers_2.c

void		ft_create_philosophers(t_table *table);
void		*ft_routine(void *data);
void		ft_end_simulation(t_table *table);

// ft_parsing.c

void		ft_init(t_table **table);
void		ft_parse(t_table *table);
void		ft_create_forks(t_table *table);

// ft_utils.c

void		ft_error(t_table *table, int error);

// ft_lib.c

void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);

# endif
