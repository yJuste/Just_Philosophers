/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
int			ft_check_death(t_philo *philo);
int			ft_check_last_meal(t_philo *philo);
// ---------------------------------------------------------

int	ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->info);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->table->info);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->info);
	return (0);
}

int	ft_check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->time);
	if (ft_gettimeofday() - philo->table->start_simulation
		- philo->last_meal > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->time);
		return (1);
	}
	pthread_mutex_unlock(&philo->time);
	return (0);
}
