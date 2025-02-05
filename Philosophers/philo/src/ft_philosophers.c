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
/*   • Débute et finit la simulation.                                         */
/* ************************************************************************** */
#include "ft_philosophers.h"

// --------------------PROTOTYPE-----------------------
void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);
// ----------------------------------------------------

// Démarre la routine des philosophes et du moniteur.
void	ft_create_philosophers(t_table *table)
{
	int		i;

	i = 0;
	pthread_create(&table->monitor, NULL, ft_monitor, table);
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].id_thread,
			NULL, ft_routine, &table->philo[i]);
		i++;
	}
}

// 1. Met un terme à la simulation.
// 2. Free, destroy les mutex.
void	ft_end_simulation(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philo[i++].id_thread, NULL);
	pthread_join(table->monitor, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->fork[i].fork);
		pthread_mutex_destroy(&table->philo[i].time);
		i++;
	}
	pthread_mutex_destroy(&table->info);
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->replete);
	free(table->philo);
	free(table->fork);
	free(table);
}
