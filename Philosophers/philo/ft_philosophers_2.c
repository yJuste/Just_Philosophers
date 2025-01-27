/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers_2.c                                :+:      :+:    :+:   */
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
void		*ft_routine(void *data);
void		ft_end_simulation(t_table *table);
// ---------------------------------------------------------

void	ft_create_philosophers(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		table->philo[i].table = table;
		pthread_create(&table->philo[i].id_thread,
			NULL, ft_routine, &table->philo[i]);
		i++;
	}
}

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	pthread_mutex_lock(&table->info);
	printf("philo %d: %d\n", table->philo->id++, table->a++);
	pthread_mutex_unlock(&table->info);
	return (NULL);
}

void	ft_end_simulation(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->nb_philo)
		pthread_join(table->philo[i].id_thread, NULL);
	i = -1;
	while (++i < table->nb_philo)
		pthread_mutex_destroy(&table->fork[i].fork);
	pthread_mutex_destroy(&table->info);
	free(table->philo);
	free(table->fork);
	free(table);
}
