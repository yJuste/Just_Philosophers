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
// ---------------------------------------------------------

void	*ft_routine(void *data)
{
	t_philo		*philo;
	t_table		*table;

	philo = (t_philo *)data;
	table = philo->table;
	while (!ft_spinlock(&table->info, &table->wait_start))
		;
	pthread_mutex_lock(&table->info);
	while (!table->end_simulation)
	{
		printf("Simu not finished\n");
		printf("No way %d\n", philo->id);
		table->end_simulation = 1;
	}
	pthread_mutex_unlock(&table->info);
	return (NULL);
}
