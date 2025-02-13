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
// 3. Les fourchettes sont désormais accessibles pour tous les philosophes.
int	ft_init(t_table **table, char **argv)
{
	(*table) = ft_calloc(1, sizeof(t_table));
	if (ft_parse(*table, argv, 0) == 1)
		return (free(*table), 1);
	(*table)->philo = ft_calloc((*table)->nb_philo, sizeof(t_philo));
	sem_unlink("forks");
	sem_unlink("sem_info");
	sem_unlink("sem_write");
	sem_unlink("sem_replete");
	sem_unlink("sem_time");
	(*table)->forks = sem_open("forks", O_CREAT, 0, (*table)->nb_philo);
	(*table)->sem_info = sem_open("sem_info", O_CREAT, 0, 1);
	(*table)->sem_write = sem_open("sem_write", O_CREAT, 0, 1);
	(*table)->sem_replete = sem_open("sem_replete", O_CREAT, 0, 1);
	(*table)->sem_time = sem_open("sem_time", O_CREAT, 0, 1);
	ft_init_philosophers(*table);
	(*table)->start_simulation = ft_gettimeofday();
	return (0);
}

// Analyse les arguments, check atoi strict.
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

// Donne les valeurs par défaut pour chaque philosophe.
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
		philo->monitor = 0;
		philo->table = table;
		i++;
	}
}
