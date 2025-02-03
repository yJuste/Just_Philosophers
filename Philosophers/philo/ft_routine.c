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
int			ft_check_death(t_philo *philo);
void		ft_take_forks(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_die(t_philo *philo);
// ---------------------------------------------------------

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (!ft_check_death(philo))
	{
		//ft_eat(philo);
		ft_write(philo, EAT);
		pthread_mutex_lock(&philo->eat_mtx);
		philo->last_meal = ft_gettimeofday() - philo->table->start_simulation;
		pthread_mutex_unlock(&philo->eat_mtx);
		ft_usleep(philo->table->time_to_eat);
		ft_sleep(philo);
		ft_think(philo);
		philo->meals_taken++;
	}
	return (NULL);
}

// status mutex check death info
int	ft_check_death(t_philo *philo)
{
	t_table		*table;

	table = philo->table;
	pthread_mutex_lock(&table->info);
	if (table->end_simulation == 1)
	{
		pthread_mutex_unlock(&table->info);
		return (1);
	}
	pthread_mutex_unlock(&table->info);
	return (0);
}

// eat_mutex -- last_meal;
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_write(philo, LEFT_FORK);
	pthread_mutex_lock(&philo->right_fork->fork);
	ft_write(philo, RIGHT_FORK);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_write(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep);
}

void	ft_think(t_philo *philo)
{
	ft_write(philo, THINK);
}
