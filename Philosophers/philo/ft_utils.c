/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		ft_error(t_table *table, int error);
// ---------------------------------------------------------

void	ft_error(t_table *table, int error)
{
	//if (table)
	//	ft_free(table);
	if (error == 255)
		write(2, "Error\nToo few/many arguments.\n", 31);
	else
		write(2, "Error\n", 6);
}
