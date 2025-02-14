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
	int			i;
	t_table		*table;
	t_philo		*philo;

	table = (t_table *)data;
	philo = table->philo;
	while (1)
	{
		i = 0;
		while (i < philo->table->nb_philo)
		{
			if (ft_check_last_meal(&philo[i]))
			{
				ft_philo_died(table, philo[i].id);
				return (NULL);
			}
			i++;
		}
		if (ft_check_replete(philo) == 1)
			return (NULL);
		usleep(50);
	}
	return (NULL);
}

// Met fin à toute exécution et affiche le temps de sa mort.
void	ft_philo_died(t_table *table, int id)
{
	pthread_mutex_lock(&table->write);
	pthread_mutex_lock(&table->info);
	table->end_simulation = 1;
	pthread_mutex_unlock(&table->info);
	printf("%ld %d died\n",
		ft_gettimeofday() - table->start_simulation,
		id);
	pthread_mutex_unlock(&table->write);
}
