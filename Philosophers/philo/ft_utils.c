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
void		ft_write(t_philo *philo, t_actions action);
long		ft_gettimeofday(void);
void		ft_usleep(long ms);
int			ft_spinlock(t_mtx *mutex, int *wait);
// ---------------------------------------------------------

void	ft_write(t_philo *philo, t_actions action)
{
	long		elapsed;

	elapsed = ft_gettimeofday() - philo->table->start_simulation;
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
}

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

int	ft_spinlock(t_mtx *mutex, int *wait)
{
	int		spinlock;

	pthread_mutex_lock(mutex);
	spinlock = *wait;
	pthread_mutex_unlock(mutex);
	return (spinlock);
}
