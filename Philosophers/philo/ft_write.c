/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// ----------------------PROTOTYPE-----------------------
void		ft_write_status(t_philo *philo, t_actions action);
// ------------------------------------------------------

void	ft_write_status(t_philo *philo, t_actions action)
{
	long		elapsed;

	if (philo->full)
		return ;
	elapsed = ft_gettimeofday() - philo->table->start_simulation;
	pthread_mutex_lock(&philo->table->write);
	if (ft_simulation_finished(philo->table))
		return ;
	if (action == LEFT_FORK || action == RIGHT_FORK)
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
