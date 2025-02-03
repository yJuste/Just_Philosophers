/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		*ft_monitor(void *data);
int			ft_check_end(t_philo *philo);
void		ft_write(t_philo *philo, t_actions action);
// ---------------------------------------------------------

// end_simulation -- info
// las_meal -- eat_mtx
// printf -- write
void	*ft_monitor(void *data)
{
	int			i;
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (1)
	{
			if (ft_check_end(philo))
			{
				pthread_mutex_lock(&table->write);
				//ft_write(philo, DIE);
				printf("%ld %d died\n", ft_gettimeofday() - table->start_simulation, philo[i].id);
				pthread_mutex_lock(&table->info);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->info);
				pthread_mutex_unlock(&table->write);
				return (NULL);
			}
	}
	return (NULL);
}

int	ft_check_end(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mtx);
	if ( ft_gettimeofday() - philo->table->start_simulation
		- philo->last_meal > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->eat_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->eat_mtx);
	return (0);
}

/*
void	*ft_monitor(void *data)
{
	int			i;
	long		last_meal;
	t_table		*table;
	t_philo		*philo;

	table = (t_table *)data;
	while (!ft_spinlock(&table->info, &table->end_simulation))
	{
		i = 0;
		while (i < table->nb_philo)
		{
			philo = &table->philo[i];
			pthread_mutex_lock(&philo->eat_mtx);
			last_meal = philo->last_meal;
			pthread_mutex_unlock(&philo->eat_mtx);
			if (last_meal >= table->time_to_die)
			{
				ft_write(philo, DIE);
				pthread_mutex_lock(&table->info);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->info);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}*/

// write = print_mutex;
void	ft_write(t_philo *philo, t_actions action)
{
	long		elapsed;

	if (ft_check_death(philo))
		return ;
	elapsed = ft_gettimeofday() - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write);
	if (action == LEFT_FORK)
		printf("%ld %d has taken a left fork\n", elapsed, philo->id);
	else if (action == RIGHT_FORK)
		printf("%ld %d has taken a right fork\n", elapsed, philo->id);
	else if (action == EAT)
		printf("%ld %d is eating, meals: %d\n", elapsed, philo->id, philo->meals_taken);
	else if (action == SLEEP)
		printf("%ld %d is sleeping, lastmeal: %ld\n", elapsed, philo->id, philo->last_meal);
	else if (action == THINK)
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (action == DIE)
		printf("%ld %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}
