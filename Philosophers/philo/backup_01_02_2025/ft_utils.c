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
long			ft_gettimeofday(void);
void		ft_usleep(long msec, t_table *table);
void		ft_free(t_table *table);
// ---------------------------------------------------------

// gettimeofday() va overflow le 10 Mars 2037 si je mets en retour de fonction un INT.
long	ft_gettimeofday(void)
{
	long			time;
	struct timeval		current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (ft_putstr_fd("Error of gettimeofday.\n", 2), 255);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

// 1. peut interrompre l'attente si la simulation est terminée.
// 2. plus précis.
void	ft_usleep(long msec, t_table *table)
{
	long		start;
	long		elapsed;
	long		rem;

	start = ft_gettimeofday();
	while (ft_gettimeofday() - start < msec)
	{
		if (ft_simulation_finished(table))
			break ;
		elapsed = ft_gettimeofday() - start;
		rem = msec - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
		else
		{
			while (ft_gettimeofday() - start < msec)
				;
		}
	}
}

//	----------GOTO FREE----------

void	ft_free(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
		pthread_mutex_destroy(&table->fork[i++].fork);
	pthread_mutex_destroy(&table->info);
	pthread_mutex_destroy(&table->write);
	free(table->philo);
	free(table->fork);
	free(table);
}
