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
void		ft_write(t_philo *philo, t_actions action);
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
		usleep(50);
}

void	ft_write(t_philo *philo, t_actions action)
{
	long		elapsed;

	if (ft_check_death(philo))
		return ;
	elapsed = ft_gettimeofday() - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write);
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
	pthread_mutex_unlock(&philo->table->write);
}
