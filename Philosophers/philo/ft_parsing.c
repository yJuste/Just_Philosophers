/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
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
void		ft_init_philosophers(t_table *table);
// ---------------------------------------------------------

void	ft_init(t_table **table)
{
	int		i;

	(*table) = ft_calloc(1, sizeof(t_table));
	ft_parse(*table);
	(*table)->philo = ft_calloc((*table)->nb_philo, sizeof(t_philo));
	(*table)->fork = ft_calloc((*table)->nb_philo, sizeof(t_fork));
	(*table)->philo->id = 1;
	pthread_mutex_init(&(*table)->info, NULL);
	pthread_mutex_init(&(*table)->write, NULL);
	i = 0;
	while (i < (*table)->nb_philo)
		pthread_mutex_init(&(*table)->fork[i++].fork, NULL);
	(*table)->start_simulation = ft_gettimeofday();
	ft_init_philosophers(*table);
}

void	ft_parse(t_table *table)
{
	table->nb_philo = 3;
	table->time_to_die = 200;
	table->time_to_eat = 100;
	table->time_to_sleep = 100;
	table->max_meals = -1;
}

void	ft_init_philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = &table->philo[i];
		philo->id = i + 1;
		philo->last_meal = table->start_simulation;
		philo->left_fork = &table->fork[(i + 1) % table->nb_philo];
		philo->right_fork = &table->fork[i];
		if (philo->id % 2 == 0)
		{
			philo->left_fork = &table->fork[i % table->nb_philo];
			philo->right_fork = &table->fork[i + 1];
		}
		pthread_mutex_init(&philo->mtx, NULL);
		pthread_mutex_init(&philo->eat_mtx, NULL);
		philo->table = table;
		i++;
	}
}
