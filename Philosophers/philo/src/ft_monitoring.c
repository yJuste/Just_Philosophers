/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitoring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated: 2025/02/04 18:23:43 by jlongin          ###   ########.fr       */
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
		if (ft_check_replete(philo) == 1)
			return (NULL);
		while (i < philo->table->nb_philo)
		{
			if (ft_check_last_meal(&philo[i]))
			{
				pthread_mutex_lock(&table->write);
				pthread_mutex_lock(&table->info);
				table->end_simulation = 1;
				pthread_mutex_unlock(&table->info);
				printf("%ld %d died\n",
					ft_gettimeofday() - table->start_simulation,
					philo->id);
				pthread_mutex_unlock(&table->write);
				return (NULL);
			}
			i++;
		}
		ft_usleep(1);
	}
	return (NULL);
}
