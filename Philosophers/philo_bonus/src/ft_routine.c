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
/*   • Lancement de la simulation.                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------------PROTOTYPE--------------------------------
void		*ft_routine(void *data);
// ----------------------------------------------------------------------

// Chaque philosophe vie sa routine, manger, dormir, penser.
void	*ft_routine(void *data)
{
	t_table		*table;
	t_philo		*philo;

	philo = (t_philo *)data;
	table = philo->table;
	return (NULL);
}
