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
	max_meals = 0;
	philo = (t_philo *)data;
	table = philo->table;
	if (table->max_meals == 0)
		return (ft_i_am_replete(philo), NULL);
	while (!ft_check_death())
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
		sem_wait(philo->table->forks);
		ft_write(philo, LEFT_FORK);
		ft_usleep(philo->table->time_to_die);
		ft_write(philo, DIE);
		sem_post(philo->table->forks);
		return (1);
	}
	if (philo->last_meal == 0 && philo->id % 2 == 0)
		ft_avoid_deadlock(philo, max_meals, flg);
	else
	{
		ft_usleep_max_meals(philo->table->time_to_eat / 2,
			philo, max_meals, flg);
		ft_avoid_deadlock(philo, max_meals, flg);
	}
	return (0);
}

// 1. Les impairs commencent à manger, ensuite ca reprend naturellement.
// 2. Eviter les interblocages.
int	ft_avoid_deadlock(t_philo *philo, int *max_meals, int *flg)
{
	sem_wait(philo->table->forks);
	ft_write(philo, LEFT_FORK);
	sem_wait(philo->table->forks);
	ft_write(philo, RIGHT_FORK);
	ft_write(philo, EAT);
	sem_wait(philo->table->sem_time);
	philo->last_meal = ft_gettimeofday() - philo->table->start_simulation;
	sem_post(philo->table->sem_time);
	ft_usleep_max_meals(philo->table->time_to_eat, philo, max_meals, flg);
	(*max_meals)++;
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
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
