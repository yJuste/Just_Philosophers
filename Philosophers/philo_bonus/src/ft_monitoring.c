/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   • Contrôle le déroulement de la simulation.                              */
/* ************************************************************************** */
#include "ft_philosophers.h"

// --------------------PROTOTYPE----------------------
void		*ft_monitor(void *data);
void		ft_philo_died(t_table *table, int id);
// ---------------------------------------------------

// Surveille les philosophes et gère le cas de mort et de repas pris.
void	*ft_monitor(void *data)
{
	t_table		*table;
	t_philo		*philo;

	table = (t_table *)data;
	philo = table->philo;
	while (1)
	{
		if (ft_check_last_meal(philo))
		{
			ft_philo_died(table, philo->id);
			return (NULL);
		}
		if (ft_check_replete(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

// Met fin à toute exécution et affiche le temps de sa mort.
void	ft_philo_died(t_table *table, int id)
{
	sem_wait(table->sem_write);
	sem_wait(table->sem_info);
	table->end_simulation = 1;
	sem_post(table->sem_info);
	printf("%ld %d died\n",
		ft_gettimeofday() - table->start_simulation,
		id);
	sem_post(table->sem_write);
}
