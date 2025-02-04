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
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		*ft_monitor(void *data);
// ---------------------------------------------------------

void	*ft_monitor(void *data)
{
	int			i;
	t_table		*table;
	t_philo		*philo;

	i = 0;
	table = (t_table *)data;
	philo = table->philo;
	while (1)
	{
		i = 0;
		while (i < philo->table->nb_philo)
		{
			if (ft_check_last_meal(&philo[i]))
			{
				ft_write(&philo[i], DIE);
				pthread_mutex_lock(&table->info);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->info);
				return (NULL);
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
