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
int			ft_init(t_table **table, char **argv);
int			ft_parse(t_table *table, char **argv);
void		ft_init_philosophers(t_table *table);
// ---------------------------------------------------------

int	ft_init(t_table **table, char **argv)
{
	int		i;

	i = 0;
	(*table) = ft_calloc(1, sizeof(t_table));
	if (ft_parse(*table, argv) == 1)
		return (1);
	/*(*table)->philo = ft_calloc((*table)->nb_philo, sizeof(t_philo));
	(*table)->fork = ft_calloc((*table)->nb_philo, sizeof(t_fork));
	pthread_mutex_init(&(*table)->info, NULL);
	pthread_mutex_init(&(*table)->write, NULL);
	while (i < (*table)->nb_philo)
		pthread_mutex_init(&(*table)->fork[i++].fork, NULL);
	(*table)->start_simulation = ft_gettimeofday();
	ft_init_philosophers(*table);*/
	return (0);
}

int	ft_parse(t_table *table, char **argv)
{
	int		i;

	i = 1;
	while (i < 5)
		if (ft_check_atoi(argv[i++], 1) == 1)
			return (1);
	table->nb_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		if (ft_check_atoi(argv[5], 1) == 1)
			return (1);
		table->max_meals = ft_atoi(argv[5]);
	}
	return (0);
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
			philo->left_fork = &table->fork[i % table->nb_philo];
		if (philo->id % 2 == 0)
			philo->right_fork = &table->fork[i + 1];
		pthread_mutex_init(&philo->time, NULL);
		philo->table = table;
		i++;
	}
}
