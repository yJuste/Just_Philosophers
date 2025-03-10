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
/*   • Fonctions de check.                                                    */
/* ************************************************************************** */
#include "ft_philosophers.h"

// -------------------------PROTOTYPE--------------------------
int			ft_check_death(void);
int			ft_check_last_meal(t_philo *philo);
int			ft_check_replete(t_philo *philo);
int			ft_check_atoi(const char *s, int sign);
int			ft_check_int_min(const char *s);
// ------------------------------------------------------------

// Fonction qui check la mort du philosophe.
int	ft_check_death(void)
{
	sem_t		*die;

	die = sem_open("sem_die", 0);
	if (die == SEM_FAILED)
		return (1);
	sem_close(die);
	return (0);
}

// Fonction qui check la dernière fois que le philosophe prend sont repas.
int	ft_check_last_meal(t_philo *philo)
{
	sem_wait(philo->table->sem_time);
	if (ft_gettimeofday() - philo->table->start_simulation
		- philo->last_meal > philo->table->time_to_die)
	{
		sem_post(philo->table->sem_time);
		return (1);
	}
	sem_post(philo->table->sem_time);
	return (0);
}

// Fonction qui check si le philosophe est repu.
int	ft_check_replete(t_philo *philo)
{
	sem_wait(philo->table->sem_replete);
	if (philo->full == 1)
	{
		sem_post(philo->table->sem_replete);
		return (1);
	}
	sem_post(philo->table->sem_replete);
	return (0);
}

// Fonction qui check atoi (sans exit());
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
