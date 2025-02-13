/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   • Débute et finit la simulation.                                         */
/* ************************************************************************** */
#include "ft_philosophers.h"

// --------------------PROTOTYPE-----------------------
void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);
// ----------------------------------------------------

// Démarre la routine des philosophes et du moniteur.
void	ft_create_philosophers(t_table *table)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < table->nb_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			pthread_create(&table->philo[i].monitor, NULL,
				ft_monitor, &table->philo[i]);
			ft_routine(&table->philo[i]);
			pthread_join(table->philo[i].monitor, NULL);
			return (exit(0));
		}
		i++;
	}
}

// 1. Met un terme à la simulation.
// 2. Free, destroy les mutex.
void	ft_end_simulation(t_table *table)
{
	int		i;

	i = -1;
	while (++i < table->nb_philo)
		waitpid(-1, NULL, 0);
	sem_close(table->forks);
	sem_close(table->sem_info);
	sem_close(table->sem_write);
	sem_close(table->sem_replete);
	sem_close(table->sem_time);
	sem_unlink("forks");
	sem_unlink("sem_info");
	sem_unlink("sem_write");
	sem_unlink("sem_replete");
	sem_unlink("sem_time");
	free(table->philo);
	free(table);
}
