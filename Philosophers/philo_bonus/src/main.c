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
/*   • Résoud le dîner des philosophes.                                       */
/*   • ./philo [ nb_hilo ] [ die ] [ eat ] [ sleep ] ([ max_meals ])          */
/*      -> nb_philo  - number_of_philosophers                                 */
/*      -> die       - time_to_die                                 [ in ms ]  */
/*      -> eat       - time_to_eat                                 [ in ms ]  */
/*      -> sleep     - time_to_sleep                               [ in ms ]  */
/*      -> max_meals - number_of_times_each_philosopher_must_eat              */
/* ************************************************************************** */
#include "ft_philosophers.h"

int	main(int argc, char **argv)
{
	t_table		*table;

	if (argc != 5 && argc != 6)
		return (ft_putstr_fd("Too few/many arguments.\n", 2), 1);
	if (ft_init(&table, argv) == 1)
		return (1);
	ft_create_philosophers(table);
	ft_end(table);
	return (0);
}
