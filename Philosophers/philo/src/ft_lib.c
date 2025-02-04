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
/*   • First Lib.                                                             */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
int			ft_atoi(const char *s);
void		*ft_calloc(size_t count, size_t size);
void		ft_putstr_fd(char *s, int fd);
// ---------------------------------------------------------

int	ft_atoi(const char *s)
{
	int		sign;
	int		res;

	sign = 1;
	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		sign = -sign;
	if (*s == '-' || *s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
		res = res * 10 + (*s++ - '0');
	return (sign * res);
}

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

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}
