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

// -----------------------PROTOTYPE--------------------
void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);
// ----------------------------------------------------

void	ft_create_philosophers(t_table *table)
{
	int		i;

	if (!table->max_meals)
		return ;
	if (table->nb_philo == 1)
		return ;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].id_thread,
			NULL, ft_routine, &table->philo[i]);
		i++;
	}
	pthread_create(&table->monitor, NULL, ft_monitor, table);
	table->start_simulation = ft_gettimeofday();
	pthread_mutex_lock(&table->info);
	table->wait_start = 1;
	pthread_mutex_unlock(&table->info);
}

void	ft_end_simulation(t_table *table)
{
	int		i;

	i = 0;
	if (!table->end_simulation)
		while (i < table->nb_philo)
			pthread_join(table->philo[i++].id_thread, NULL);
	pthread_join(table->monitor, NULL);
	ft_free(table);
}
