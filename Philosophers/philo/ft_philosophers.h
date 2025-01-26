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

// thread
# include <pthread.h>

// gettimeofday
#include <sys/time.h>

// Structures

typedef struct pthread_mutex_t	t_mtx;
typedef struct s_table		t_table;
typedef struct s_philo		t_philo;
typedef struct s_fork		t_fork;

typedef struct s_table
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			meals_taken;
	t_philo		*philo;
}	t_table;

typedef struct s_philo
{
	int			id;
	pthread_t	id_thread;
}	t_philo;

typedef struct s_fork
{
}	t_fork;

//	---------- MY CODE ----------

// ft_philosophers.c

// ft_utils.c

void		ft_error(t_table *table, int error);

// ft_lib.c

void		*ft_calloc(size_t count, size_t size);

# endif
