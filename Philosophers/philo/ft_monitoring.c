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
void		ft_write(t_philo *philo, t_actions action);
// ---------------------------------------------------------

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
			pthread_mutex_lock(&philo->mtx);
			last_meal = philo->last_meal;
			pthread_mutex_unlock(&philo->mtx);
			if (last_meal >= table->time_to_die)
			{
				ft_write(philo, DIE);
				pthread_mutex_lock(&table->info);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->info);
				return (NULL);
			}
			ft_usleep(1);
			i++;
		}
	}
	return (NULL);
}

void	ft_write(t_philo *philo, t_actions action)
{
	long		elapsed;

	pthread_mutex_lock(&philo->table->info);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->table->info);
		return ;
	}
	pthread_mutex_unlock(&philo->table->info);
	elapsed = ft_gettimeofday() - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write);
	if (action == LEFT_FORK)
		printf("%ld %d has taken a left fork\n", elapsed, philo->id);
	else if (action == RIGHT_FORK)
		printf("%ld %d has taken a right fork\n", elapsed, philo->id);
	else if (action == EAT)
		printf("%ld %d is eating\n", elapsed, philo->id);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", elapsed, philo->id);
	else if (action == THINK)
		printf("%ld %d is thinking\n", elapsed, philo->id);
	else if (action == DIE)
		printf("%ld %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->write);
}
