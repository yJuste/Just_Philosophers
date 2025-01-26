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
t_table		*ft_init(void);
void		ft_create_philosophers(t_table *table);
void		ft_end_simulation(t_table *table);
void		*ft_routine(void *data);
// ---------------------------------------------------------

static pthread_mutex_t	c;
static int		a = 0;

//if (argc != 5 || argc != 6)
//	return (ft_error(table, 255), 255);
int	main(int argc, const char **argv)
{
	t_table		*table;

	table = ft_init();
	pthread_mutex_init(&c, NULL);
	ft_create_philosophers(table);
	ft_end_simulation(table);
	pthread_mutex_destroy(&c);
	free(table);
	return (0);
}

void	ft_end_simulation(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i].id_thread, NULL);
		i++;
	}
}

void	ft_create_philosophers(t_table *table)
{
	int			i;

	i = 0;
	table->nb_philo = 5;
	table->philo = ft_calloc(table->nb_philo, sizeof(t_philo));
	while (i < table->nb_philo)
	{
		pthread_create(&table->philo[i].id_thread,
			NULL, ft_routine, &table->philo[i]);
		i++;
	}
}

t_table	*ft_init(void)
{
	t_table		*table;

	table = ft_calloc(1, sizeof(t_table));
	return (table);
}

void	*ft_routine(void *data)
{
	pthread_mutex_lock(&c);
	printf("%d", a++);
	pthread_mutex_unlock(&c);
	return (NULL);
}

