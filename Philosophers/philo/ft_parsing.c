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
// ---------------------------------------------------------

void	ft_init(t_table **table)
{
	(*table) = ft_calloc(1, sizeof(t_table));
	(*table)->fork = ft_calloc(1, sizeof(t_fork));
	ft_parse(*table);
	(*table)->philo = ft_calloc((*table)->nb_philo, sizeof(t_philo));
	(*table)->philo->id = 1;
	pthread_mutex_init(&(*table)->info, NULL);
}

void	ft_parse(t_table *table)
{
	table->nb_philo = 5;
	table->time_to_die = 500;
	table->time_to_eat = 500;
	table->time_to_sleep = 500;
}
