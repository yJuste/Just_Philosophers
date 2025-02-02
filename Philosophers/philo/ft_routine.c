/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		*ft_routine(void *data);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
// ---------------------------------------------------------

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (!ft_spinlock(&table->info, &table->end_simulation))
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx);
	philo->last_meal = ft_gettimeofday() - philo->table->start_simulation;
	pthread_mutex_unlock(&philo->mtx);
}

void	ft_sleep(t_philo *philo)
{
	ft_usleep(philo->table->time_to_sleep);
	ft_write(philo, SLEEP);
}

void	ft_think(t_philo *philo)
{
	ft_write(philo, THINK);
}
