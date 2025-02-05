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
void		ft_i_am_replete(t_table *table);
// ---------------------------------------------------------

void	*ft_routine(void *data)
{
	int			meals_taken;
	t_table		*table;
	t_philo		*philo;

	meals_taken = 0;
	philo = (t_philo *)data;
	table = philo->table;
	if (table->max_meals == 0)
		return (ft_i_am_replete(table), NULL);
	while (!ft_check_death(philo))
	{
		ft_eat(philo);
		if (meals_taken != -1 && meals_taken == table->max_meals - 1)
			break ;
		ft_sleep(philo);
		ft_think(philo);
		meals_taken++;
	}
	ft_i_am_replete(table);
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_write(philo, LEFT_FORK);
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

void	ft_i_am_replete(t_table *table)
{
	pthread_mutex_lock(&table->replete);
	table->full += 1;
	pthread_mutex_unlock(&table->replete);
}
