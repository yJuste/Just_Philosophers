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
void		ft_init_philosophers(t_table *table, t_philo *philo, int id);
void		*ft_routine(void *data);
void		ft_end_simulation(t_table *table);
// ---------------------------------------------------------

void	ft_create_philosophers(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		ft_init_philosophers(table, &table->philo[i], i + 1);
		pthread_create(&table->philo[i].id_thread,
			NULL, ft_routine, &table->philo[i]);
		i++;
	}
}

void	ft_init_philosophers(t_table *table, t_philo *philo, int id)
{
	philo->id = id;
	philo->left_fork = &table->fork[id % table->nb_philo];
	philo->right_fork = &table->fork[id - 1];
	philo->table = table;
}

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (1)
	{
		pthread_mutex_lock(&table->info_a);
		if (table->a + 1 == philo->id)
		{
			pthread_mutex_lock(&table->info);
			printf("philo %d: %d\n", philo->id, table->a++);
			pthread_mutex_unlock(&table->info);
		}
		pthread_mutex_unlock(&table->info_a);
		if (table->a == 5)
			break ;
	}
	return (NULL);
}

void	ft_end_simulation(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
		pthread_join(table->philo[i++].id_thread, NULL);
	printf("\n");
	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(&table->fork[i++].fork);
	pthread_mutex_destroy(&table->info);
	pthread_mutex_destroy(&table->info_a);
	free(table->philo);
	free(table->fork);
	free(table);
}
