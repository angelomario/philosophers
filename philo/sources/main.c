/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:48:37 by aquissan          #+#    #+#             */
/*   Updated: 2024/09/30 14:49:43 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	show_info(t_philo *philo, char *info)
{
	char	*color;

	if (pthread_mutex_lock(&philo->table->variable) == 0)
	{
		color = RED;
		if (!ft_strcmp(info, "is eating\n"))
			color = GREEN;
		if (!ft_strcmp(info, "is sleeping\n"))
			color = CYAN;
		if (!ft_strcmp(info, "is thinking\n"))
			color = BLUE;
		if (!ft_strcmp(info, "has taken a fork\n"))
			color = MAGENTA;
		if (!philo->table->stop)
		{
			printf("%s%ldms %d %s%s", color, (current_timestamp()
					- philo->table->time), philo->id, info, RESET);
		}
		pthread_mutex_unlock(&philo->table->variable);
	}
}

void	update_data_s_philo(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->locker) == 0)
	{
		philo->did_eat++;
		philo->last_time_eat = current_timestamp();
		pthread_mutex_unlock(&philo->locker);
	}
}

int	there_was_an_error(t_table *table, char **argv, int argc)
{
	int	i;

	i = argc - 1;
	while (i--)
	{
		table->must_eat = check_params(argc - 1, argv, &table->philos[i],
				table);
		if (!table->must_eat)
		{
			free(table->philos);
			ft_putstr_fd("Error\n", 2);
			return (1);
		}
	}
	table->qtd_philo = ft_atoi(argv[1]);
	linking_philos(table, argv);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	table->must_eat = 0;
	table->stop = 0;
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Error\n", 2);
		free(table);
	}
	else
	{
		table->philos = (t_philo *)malloc(sizeof(t_philo) * (ft_atoi(argv[1])
					+ argc));
		if (!there_was_an_error(table, argv, argc))
		{
			if (table->must_eat != 0)
				philosophers_problem(table);
			clean(table);
		}
		else
			free(table);
	}
	return (0);
}
