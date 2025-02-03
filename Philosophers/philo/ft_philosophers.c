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
void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);
// ---------------------------------------------------------

void	ft_create_philosophers(t_table *table)
{
	int		i;

	i = 0;
	pthread_create(&table->monitor1, NULL, ft_monitor, &table->philo[0]);
	pthread_create(&table->monitor2, NULL, ft_monitor, &table->philo[1]);
	pthread_create(&table->monitor3, NULL, ft_monitor, &table->philo[2]);
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].id_thread,
			NULL, ft_routine, &table->philo[i]);
		i++;
	}
}

void	ft_end_simulation(t_table *table)
{
	int		i;

	i = 0;
	if (table->end_simulation == 0)
		while (i < table->nb_philo)
			pthread_join(table->philo[i++].id_thread, NULL);
	pthread_join(table->monitor1, NULL);
	pthread_join(table->monitor2, NULL);
	pthread_join(table->monitor3, NULL);
	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(&table->fork[i++].fork);
	pthread_mutex_destroy(&table->info);
	pthread_mutex_destroy(&table->write);
	free(table->philo);
	free(table->fork);
	free(table);
}
