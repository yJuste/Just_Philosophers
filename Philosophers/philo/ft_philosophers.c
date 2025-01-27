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
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
int			main(int argc, const char **argv);
// ---------------------------------------------------------

//if (argc != 5 || argc != 6)
//	return (ft_error(table, 255), 255);
int	main(int argc, const char **argv)
{
	t_table		*table;

	table = ft_init();
	ft_create_philosophers(table);
	ft_end_simulation(table);
	free(table->philo);
	free(table);
	return (0);
}
