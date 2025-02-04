/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:                                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created:   by Just'                               #+#    #+#             */
/*   Updated:   by Just'                              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -----------------------PROTOTYPE-------------------------
int			ft_check_death(t_philo *philo);
int			ft_check_last_meal(t_philo *philo);
int			ft_check_atoi(const char *s, int sign);
int			ft_check_int_min(const char *s);
// ---------------------------------------------------------

int	ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->info);
	if (philo->table->end_simulation == 1)
	{
		pthread_mutex_unlock(&philo->table->info);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->info);
	return (0);
}

int	ft_check_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->time);
	if (ft_gettimeofday() - philo->table->start_simulation
		- philo->last_meal > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->time);
		return (1);
	}
	pthread_mutex_unlock(&philo->time);
	return (0);
}

int	ft_check_atoi(const char *s, int sign)
{
	long		res;

	sign = 1;
	res = 0;
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (ft_check_int_min(s) == 0)
		return (0);
	if (*s == '-')
		sign = -sign;
	if (*s == '-' || *s == '+')
		s++;
	if (!*s)
		return (ft_putstr_fd("Error\nAtoi, No numbers.\n", 2), 1);
	while (*s >= '0' && *s <= '9')
	{
		res = res * 10 + (*s++ - '0');
		if (res > 2147483647)
			return (ft_putstr_fd("Error\nAtoi Overflow.\n", 2), 1);
	}
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s != '\0')
		return (ft_putstr_fd("Error\nAtoi, Invalid character.\n", 2), 1);
	return (0);
}

int	ft_check_int_min(const char *s)
{
	int		flg;

	flg = 0;
	if (ft_strncmp("-2147483648", s, 11) == 0)
	{
		s += 11;
		flg = 1;
	}
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '\0' && flg == 1)
		return (0);
	return (1);
}
