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
// ---------------------------------------------------------

static pthread_mutex_t	c;
static int		a = 0;

void	*ft_routine(void *b)
{
	pthread_mutex_lock(&c);
	printf("%d", a++);
	pthread_mutex_unlock(&c);
	return (NULL);
}

int	main(int argc, const char *argv[])
{
	pthread_t	thread[3];
	t_table		*table;

	table = NULL;
	//if (argc != 5 || argc != 6)
	//	return (ft_error(table, 255), 255);
	pthread_mutex_init(&c, NULL);
	pthread_create(&thread[0], NULL, ft_routine, NULL);
	pthread_create(&thread[1], NULL, ft_routine, NULL);
	pthread_create(&thread[2], NULL, ft_routine, NULL);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);
	//pthread_mutex_destroy(&c);
	printf("\n");
	return (0);
}
