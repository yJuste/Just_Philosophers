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
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
long		ft_gettimeofday(void);
void		ft_usleep(long ms);
int		ft_check_death(t_philo *philo);
int			ft_spinlock(t_mtx *mutex, int *wait);
// ---------------------------------------------------------

long	ft_gettimeofday(void)
{
	long			time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long ms)
{
	long		start_time;

	start_time = ft_gettimeofday();
	while (ft_gettimeofday() - start_time < ms)
		usleep(10);
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

int	ft_spinlock(t_mtx *mutex, int *wait)
{
	int		spinlock;

	pthread_mutex_lock(mutex);
	spinlock = *wait;
	pthread_mutex_unlock(mutex);
	return (spinlock);
}
