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
	table->start_simulation = ft_gettimeofday();
	return ;
}

// 1. Met un terme à la simulation.
// 2. Free, destroy les mutex.
void	ft_end_simulation(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
		sem_close(table->philo[i].sem_eat);
	sem_close(table->forks);
	sem_close(table->write);
	sem_unlink(SEM_EAT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	free(table->philo);
	free(table);
}
