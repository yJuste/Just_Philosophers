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
/*   • Lancement de la simulation.                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------PROTOTYPE-------------------
void		*ft_routine(void *data);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
void		ft_i_am_replete(t_table *table);
// ---------------------------------------------

// Chaque philosophe vie sa routine, manger, dormir, penser.
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
		if (meals_taken == table->max_meals - 1)
			break ;
		ft_sleep(philo);
		ft_think(philo);
		meals_taken++;
	}
	ft_i_am_replete(table);
	return (NULL);
}

// Partie dans laquelle le philosophe doit manger.
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_write(philo, LEFT_FORK);
	if (philo->table->nb_philo == 1)
	{
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

// Partie dans laquelle le philosophe doit dormir.
void	ft_sleep(t_philo *philo)
{
	ft_write(philo, SLEEP);
	ft_usleep(philo->table->time_to_sleep);
}

// Partie dans laquelle le philosophe doit penser.
void	ft_think(t_philo *philo)
{
	ft_write(philo, THINK);
}

// Indique si le philosophe a atteint sont quota. Il est alors repu.
void	ft_i_am_replete(t_table *table)
{
	pthread_mutex_lock(&table->replete);
	table->full += 1;
	pthread_mutex_unlock(&table->replete);
}
