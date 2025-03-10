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
/*   • Analyse des nombres passés en argument.                                */
/* ************************************************************************** */
#include "ft_philosophers.h"

// ----------------------------PROTOTYPE-----------------------------
int			ft_init(t_table **table, char **argv);
int			ft_parse(t_table *table, char **argv, int i);
void		ft_init_philosophers(t_table *table);
// ------------------------------------------------------------------

// 1. Initialise tous à 0 (aussi les mutex).
// 2. Alloue de la mémoire pour les philosophes & les fourchettes.
int	ft_init(t_table **table, char **argv)
{
	int		i;

	(*table) = ft_calloc(1, sizeof(t_table));
	if (ft_parse(*table, argv, 0) == 1)
		return (free(*table), 1);
	(*table)->philo = ft_calloc((*table)->nb_philo, sizeof(t_philo));
	(*table)->fork = ft_calloc((*table)->nb_philo, sizeof(t_fork));
	pthread_mutex_init(&(*table)->info, NULL);
	pthread_mutex_init(&(*table)->write, NULL);
	pthread_mutex_init(&(*table)->replete, NULL);
	i = 0;
	while (i < (*table)->nb_philo)
		pthread_mutex_init(&(*table)->fork[i++].fork, NULL);
	i = -1;
	while (++i < (*table)->nb_philo)
		(*table)->fork[i].id = i;
	(*table)->start_simulation = ft_gettimeofday();
	ft_init_philosophers(*table);
	return (0);
}

// Analyse la map, check atoi strict.
int	ft_parse(t_table *table, char **argv, int i)
{
	i = 1;
	while (i < 5)
		if (ft_check_atoi(argv[i++], 1) == 1)
			return (1);
	i = 1;
	while (i < 5)
		if (ft_atoi(argv[i++]) <= 0)
			return (ft_putstr_fd("Error\nZero or Negative number.\n", 2), 1);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->max_meals = -1;
	if (argv[5])
	{
		if (ft_check_atoi(argv[5], 1) == 1)
			return (1);
		if (ft_atoi(argv[5]) < 0)
			return (ft_putstr_fd("Error\nNegative number.\n", 2), 1);
		table->max_meals = ft_atoi(argv[5]);
	}
	return (0);
}

// 1. Donne les valeurs par défaut pour chaque philosophe.
// 2. Lui assigne les fourchettes.
void	ft_init_philosophers(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nb_philo)
	{
		philo = &table->philo[i];
		philo->id = i + 1;
		philo->last_meal = 0;
		philo->left_fork = &table->fork[i % table->nb_philo];
		philo->right_fork = &table->fork[(i + 1) % table->nb_philo];
		pthread_mutex_init(&philo->time, NULL);
		philo->table = table;
		i++;
	}
}
