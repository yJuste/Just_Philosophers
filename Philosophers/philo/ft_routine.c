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
	t_table		*table;
	t_philo		*philo;

	philo = (t_philo *)data;
	table = philo->table;
	table->i = 0;
	while (!ft_is_died(philo))
	{
		printf("id: %d, i:%d\n", philo->id, table->i);
		table->i++;
	}
	return (NULL);
}
