/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		ft_init(t_table **table);
void		ft_parse(t_table *table);
void		ft_forks(t_table *table, t_philo *philo, int pos);
void		ft_init_philosophers(t_table *table);
// ---------------------------------------------------------

void	ft_init(t_table **table)
{
	int		i;

	(*table) = ft_calloc(1, sizeof(t_table));
	ft_parse(*table);
	(*table)->fork = ft_calloc((*table)->nb_philo, sizeof(t_fork));
	(*table)->philo = ft_calloc((*table)->nb_philo, sizeof(t_philo));
	(*table)->philo->id = 1;
	pthread_mutex_init(&(*table)->info, NULL);
	pthread_mutex_init(&(*table)->write, NULL);
	i = 0;
	while (i < (*table)->nb_philo)
		pthread_mutex_init(&(*table)->fork[i++].fork, NULL);
	ft_init_philosophers(*table);
}

void	ft_parse(t_table *table)
{
	table->nb_philo = 2;
	table->time_to_die = 100;
	table->time_to_eat = 100;
	table->time_to_sleep = 100;
	table->max_meals = -1;
	table->wait_start = 0;
}

void	ft_forks(t_table *table, t_philo *philo, int pos)
{
	philo->left_fork = &table->fork[(pos + 1) % table->nb_philo];
	philo->right_fork = &table->fork[pos];
	if (pos % 2 == 0)
	{
		philo->left_fork = &table->fork[pos];
		philo->right_fork = &table->fork[(pos + 1) % table->nb_philo];
	}
}

void	ft_init_philosophers(t_table *table)
{
	int			i;
	t_philo		*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals_taken = 0;
		ft_forks(table, philo, i);
		pthread_mutex_init(&philo->mutex, NULL);
		philo->table = table;
		i++;
	}
}
