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
/*   • Contrôle le déroulement de la simulation.                              */
/* ************************************************************************** */
#include "ft_philosophers.h"

// --------------------PROTOTYPE----------------------
void		*ft_monitor(void *data);
void		ft_philo_died(t_table *table, int id);
void		ft_philo_replete(t_table *table);
// ---------------------------------------------------

// Surveille un philosopher et gère le cas de sa mort et de ses repas pris.
void	*ft_monitor(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (1)
	{
		sem_wait(table->sem_write);
		if (ft_check_death(philo))
			return (sem_post(table->sem_write), NULL);
		if (ft_check_last_meal(philo))
			return (ft_philo_died(table, philo->id), NULL);
		if (ft_check_replete(philo))
			return (ft_philo_replete(table), NULL);
		sem_post(table->sem_write);
	}
	return (NULL);
}

// Met fin à toute exécution et affiche le temps de sa mort.
void	ft_philo_died(t_table *table, int id)
{
	sem_t		*die;

	sem_unlink("sem_die");
	die = sem_open("sem_die", O_CREAT, PERMS, 0);
	printf("%ld %d died\n",
		ft_gettimeofday() - table->start_simulation,
		id);
	sem_close(die);
	sem_post(table->sem_write);
}

void	ft_philo_replete(t_table *table)
{
	sem_t		*die;

	sem_unlink("sem_die");
	die = sem_open("sem_die", O_CREAT, PERMS, 0);
	sem_close(die);
	sem_post(table->sem_write);
}
