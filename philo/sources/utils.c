/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:14:59 by aquissan          #+#    #+#             */
/*   Updated: 2024/09/30 15:19:52 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	nb = 0;
	while (ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	return (nb * sign);
}

int	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (fd < 0 || fd > 2)
		return (1);
	write(fd, str, i);
	return (0);
}

unsigned long	current_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
