/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   • Fonctions de temps et de statuts.                                      */
/* ************************************************************************** */
#include "ft_philosophers.h"

// ----------------------PROTOTYPE-------------------------
long		ft_gettimeofday(void);
void		ft_usleep(long ms);
void		ft_usleep_max_meals(long ms, t_philo *philo,
				int *max_meals, int *flg);
void		ft_write(t_philo *philo, t_actions action);
// --------------------------------------------------------

// Calcule le temps actuel en milliseconde.
long	ft_gettimeofday(void)
{
	long			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

// Usleep amélioré qui attent vraiment le temps nécessaire grâce à gettimeofday.
void	ft_usleep(long ms)
{
	long		start_time;

	start_time = ft_gettimeofday();
	while (ft_gettimeofday() - start_time < ms)
		usleep(50);
}

void	ft_usleep_max_meals(long ms, t_philo *philo, int *max_meals, int *flg)
{
	long		start_time;

	start_time = ft_gettimeofday();
	usleep(50);
	if (*max_meals == philo->table->max_meals && *flg == 0)
	{
		ft_i_am_replete(philo);
		*flg = 1;
	}
	while (ft_gettimeofday() - start_time < ms)
		usleep(50);
}

// Écrit le statut du philosophe.
void	ft_write(t_philo *philo, t_actions action)
{
	long		elapsed;

	pthread_mutex_lock(&philo->table->write);
	elapsed = ft_gettimeofday() - philo->table->start_simulation;
	if (!ft_check_death(philo))
	{
		if (action == LEFT_FORK)
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (action == RIGHT_FORK)
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (action == EAT)
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (action == SLEEP)
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (action == THINK)
			printf("%ld %d is thinking\n", elapsed, philo->id);
		else if (action == DIE)
			printf("%ld %d died\n", elapsed, philo->id);
	}
	pthread_mutex_unlock(&philo->table->write);
}
