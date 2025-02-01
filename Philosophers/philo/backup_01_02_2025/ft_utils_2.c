/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -------------------------PROTOTYPE--------------------------
void		ft_wait_philosophers(t_table *table, int *wait);
int			ft_wait(t_mtx *mutex, int *wait);
int			ft_is_died(t_philo *philo);
int			ft_simulation_finished(t_table *table);
// ------------------------------------------------------------

// setbool, getlong ->lock, unlock
// SpinLock = boucle infinie qui attend la disponibilité d'un thread.
void	ft_wait_philosophers(t_table *table, int *wait)
{
	while (!ft_wait(&table->info, wait))
		;
}

int	ft_wait(t_mtx *mutex, int *wait)
{
	int		res;

	pthread_mutex_lock(mutex);
	res = *wait;
	pthread_mutex_unlock(mutex);
	return (res);
}

int	ft_is_died(t_philo *philo)
{
	long		elapsed;
	long		last_meal;

	pthread_mutex_lock(&philo->mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->mutex);
	elapsed = ft_gettimeofday() - last_meal;
	if (elapsed > philo->table->time_to_die)
		return (1);
	return (0);
}

int	ft_simulation_finished(t_table *table)
{
	int		end;

	pthread_mutex_lock(&table->info);
	end = table->end_simulation;
	pthread_mutex_unlock(&table->info);
	return (end);
}
