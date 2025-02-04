/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*   • Second Lib for strict_atoi.                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
int		ft_check_atoi(const char *s, int sign);
int		ft_check_int_min(const char *s, int sign);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// ---------------------------------------------------------

int	ft_check_atoi(const char *s, int sign)
{
	long		res;

	sign = 1;
	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-')
		sign = -sign;
	if (*s == '-' || *s == '+')
		s++;
	if (ft_check_int_min(s, sign) == 0)
		return (0);
	if (!*s)
		return (ft_putstr_fd("Error\nAtoi.\n", 2), 1);
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s++ - '0');
		if (res > INT_MAX)
			return (ft_putstr_fd("Error\nAtoi Overflow.\n", 2), 1);
	}
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s != '\0')
		return (ft_putstr_fd("Error\nAtoi.\n", 2), 1);
	return (0);
}

int	ft_check_int_min(const char *s, int sign)
{
	if (sign != -1)
		return (1);
	if (ft_strncmp("2147483648", s, 10) == 0)
		s += 10;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '\0')
		return (0);
	return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] && s2[i] && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
