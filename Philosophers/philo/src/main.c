/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

int	main(int argc, char **argv)
{
	t_table		*table;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Too few/many arguments.\n", 2), 1);
	if (ft_init(&table, argv) == 1)
		return (1);
	//ft_create_philosophers(table);
	//ft_end_simulation(table);
	return (0);
}
