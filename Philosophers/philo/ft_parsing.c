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
void		ft_create_forks(t_table *table);
// ---------------------------------------------------------

void	ft_init(t_table **table)
{
	(*table) = ft_calloc(1, sizeof(t_table));
	ft_parse(*table);
	(*table)->fork = ft_calloc((*table)->nb_philo, sizeof(t_fork));
	(*table)->philo = ft_calloc((*table)->nb_philo, sizeof(t_philo));
	(*table)->philo->id = 1;
	pthread_mutex_init(&(*table)->info, NULL);
	pthread_mutex_init(&(*table)->info_a, NULL);
	ft_create_forks(*table);
}

void	ft_parse(t_table *table)
{
	table->nb_philo = 5;
	table->time_to_die = 500;
	table->time_to_eat = 500;
	table->time_to_sleep = 500;
}

void	ft_create_forks(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_init(&table->fork[i++].fork, NULL);
}
