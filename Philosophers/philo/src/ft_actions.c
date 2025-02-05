/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
// ---------------------------------------------------------

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_write(philo, LEFT_FORK);
	if (philo->table->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->time);
		philo->last_meal = ft_gettimeofday() - philo->table->start_simulation;
		pthread_mutex_unlock(&philo->time);
		ft_usleep(philo->table->time_to_die);
		ft_write(philo, DIE);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return ;
	}
	pthread_mutex_lock(&philo->right_fork->fork);
	ft_write(philo, RIGHT_FORK);
	ft_write(philo, EAT);
	pthread_mutex_lock(&philo->time);
	philo->last_meal = ft_gettimeofday() - philo->table->start_simulation;
	pthread_mutex_unlock(&philo->time);
	ft_usleep(philo->table->time_to_eat);
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
