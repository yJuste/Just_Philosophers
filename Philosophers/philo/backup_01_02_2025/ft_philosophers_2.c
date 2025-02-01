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

// ----------------------PROTOTYPE-----------------------
void		*ft_routine(void *data);
void		*ft_monitor(void *data);
void		ft_eat(t_table *table, t_philo *philo);
void		ft_sleep(t_table *table, t_philo *philo);
void		ft_think(t_table *table, t_philo *philo);
// ------------------------------------------------------

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	ft_wait_philosophers(table, &table->wait_start);
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = ft_gettimeofday();
	pthread_mutex_unlock(&philo->mutex);
	while (ft_simulation_finished(table) != 1)
	{
		if (philo->full)
			break ;
		ft_eat(table, philo);
		ft_sleep(table, philo);
		ft_think(table, philo);
	}
	return (NULL);
}

void	*ft_monitor(void *data)
{
	int			i;
	t_table		*table;

	table = (t_table *)data;
	ft_wait_philosophers(table, &table->wait_start);
	while (ft_simulation_finished(table) != 1)
	{
		i = 0;
		while (i < table->nb_philo && ft_simulation_finished(table) != 1)
		{
			if (ft_is_died(&table->philo[i]) == 1)
			{
				pthread_mutex_lock(&table->info);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->info);
				ft_write_status(&table->philo[i], DIE);
			}
			i++;
		}
	}
	return (NULL);
}

void	ft_eat(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_write_statusd(philo, LEFT_FORK);
	pthread_mutex_lock(&philo->right_fork->fork);
	ft_write_statusd(philo, RIGHT_FORK);
	pthread_mutex_lock(&philo->mutex);
	philo->last_meal = ft_gettimeofday();
	pthread_mutex_unlock(&philo->mutex);
	philo->meals_taken++;
	ft_write_statusd(philo, EAT);
	ft_usleep(table->time_to_eat, table);
	if (table->max_meals > 0 && philo->meals_taken == table->max_meals)
	{
		pthread_mutex_lock(&philo->mutex);
		philo->full = 1;
		pthread_mutex_unlock(&philo->mutex);
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	ft_sleep(t_table *table, t_philo *philo)
{
	ft_write_status(philo, SLEEP);
	ft_usleep(table->time_to_sleep, table);
}

void	ft_think(t_table *table, t_philo *philo)
{
	ft_write_status(philo, THINK);
}
