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

// -----------------------------PROTOTYPE--------------------------------
void		*ft_routine(void *data);
int			ft_eat(t_philo *philo, int *max_meals, int *flg);
int			ft_avoid_deadlock(t_philo *philo,
				int *max_meals, int *flg);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
// ----------------------------------------------------------------------

// Chaque philosophe vie sa routine, manger, dormir, penser.
void	*ft_routine(void *data)
{
	int			max_meals;
	int			flg;
	t_table		*table;
	t_philo		*philo;

	flg = 0;
	max_meals = 1;
	philo = (t_philo *)data;
	table = philo->table;
	if (table->max_meals == 0)
		return (ft_i_am_replete(philo), NULL);
	while (!ft_check_death(philo))
	{
		ft_think(philo);
		if (ft_eat(philo, &max_meals, &flg) == 1)
			break ;
		ft_sleep(philo);
	}
	ft_i_am_replete(philo);
	return (NULL);
}

// Partie dans laquelle le philosophe doit manger.
int	ft_eat(t_philo *philo, int *max_meals, int *flg)
{
	if (philo->table->nb_philo == 1)
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		ft_write(philo, LEFT_FORK);
		ft_usleep(philo->table->time_to_die);
		ft_write(philo, DIE);
		pthread_mutex_unlock(&philo->left_fork->fork);
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork);
		ft_write(philo, RIGHT_FORK);
		pthread_mutex_lock(&philo->left_fork->fork);
		ft_write(philo, LEFT_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork);
		ft_write(philo, LEFT_FORK);
		pthread_mutex_lock(&philo->right_fork->fork);
		ft_write(philo, RIGHT_FORK);
	}
	ft_avoid_deadlock(philo, max_meals, flg);
	return (0);
}

// 1. Les impairs commencent à manger, ensuite ca reprend naturellement.
// 2. Eviter les interblocages.
int	ft_avoid_deadlock(t_philo *philo, int *max_meals, int *flg)
{
	ft_write(philo, EAT);
	pthread_mutex_lock(&philo->time);
	philo->last_meal = ft_gettimeofday() - philo->table->start_simulation;
	pthread_mutex_unlock(&philo->time);
	ft_usleep_max_meals(philo->table->time_to_eat, philo, max_meals, flg);
	(*max_meals)++;
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
	return (0);
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
