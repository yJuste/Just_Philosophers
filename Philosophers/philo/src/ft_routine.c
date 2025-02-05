/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		*ft_routine(void *data);
void		ft_i_am_replete(t_table *table);
// ---------------------------------------------------------

void	*ft_routine(void *data)
{
	int			meals_taken;
	t_table		*table;
	t_philo		*philo;

	meals_taken = 0;
	philo = (t_philo *)data;
	table = philo->table;
	if (table->max_meals == 0)
		return (ft_i_am_replete(table), NULL);
	while (!ft_check_death(philo))
	{
		ft_eat(philo);
		if (meals_taken != -1 && meals_taken == table->max_meals - 1)
			break ;
		ft_sleep(philo);
		ft_think(philo);
		meals_taken++;
	}
	ft_i_am_replete(table);
	return (NULL);
}

void	ft_i_am_replete(t_table *table)
{
	pthread_mutex_lock(&table->replete);
	table->full += 1;
	pthread_mutex_unlock(&table->replete);
}
