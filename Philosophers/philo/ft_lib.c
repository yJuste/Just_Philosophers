/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
void		*ft_calloc(size_t count, size_t size);
// ---------------------------------------------------------

void	*ft_calloc(size_t count, size_t size)
{
	size_t		i;
	size_t		tot;
	void		*ptr;

	i = 0;
	tot = count * size;
	ptr = malloc(tot);
	if (!ptr)
		return (NULL);
	while (i < tot)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
