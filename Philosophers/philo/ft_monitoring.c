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
int			ft_is_died(t_philo *philo);
void		*ft_monitor(void *data);
// ---------------------------------------------------------

int	ft_is_died(t_philo *philo)
{
	if (philo->table->i == 1)
		return (1);
	return (0);
}

void	*ft_monitor(void *data)
{
	int			i;
	t_table		*table;
	t_philo		*philo;

	i = 0;
	table = (t_table *)data;
	philo = table->philo;
	while (!ft_is_died(philo))
	{
		if (table->i == table->nb_philo)
		{
			printf("stop\n");
			return (NULL);
		}
	}
	return (NULL);
}
