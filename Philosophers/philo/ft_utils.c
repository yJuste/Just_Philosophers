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
void		ft_usleep(long msec);
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
	return (0);
}

void	ft_usleep(long msec)
{
	return ;
}
