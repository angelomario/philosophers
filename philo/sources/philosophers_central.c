/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_central.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:21:33 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/07 16:21:40 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophers_problem(t_table *table)
{
	int	i;

	i = -1;
	table->time = current_timestamp();
	mutexes_init(table);
	while (++i < table->qtd_philo)
	{
		pthread_create(&table->philos[i].thread, NULL, philosopher_day,
			&table->philos[i]);
		usleep(100);
	}
	create_death_check(table);
	while (i--)
		pthread_join(table->philos[i].thread, NULL);
}

void	*philosopher_day(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	while (1)
	{
		pthread_mutex_lock(&philo->table->variable);
		if (philo->table->stop || philo->is_died)
		{
			pthread_mutex_unlock(&philo->table->variable);
			break ;
		}
		pthread_mutex_unlock(&philo->table->variable);
		runs(philo);
	}
	return (NULL);
}

void	*death(void *philos)
{
	t_table	*table;

	table = (t_table *)philos;
	while (1)
	{
		if (someones_died_or_all_ate(table))
		{
			return (NULL);
		}
	}
	return (NULL);
}

void	one_philo(t_philo *philo, int *is_died)
{
	while (!(*is_died))
	{
		*is_died = someones_died_or_all_ate(philo->table);
		if (*is_died)
			get_or_leave_fork_one(philo, 0);
	}
}

void	runs(t_philo *philo)
{
	int	is_died;

	pthread_mutex_lock(&philo->locker);
	is_died = philo->is_died;
	pthread_mutex_unlock(&philo->locker);
	get_or_leave_fork_one(philo, 1);
	show_info(philo, "has taken a fork\n");
	philo->fork_left = 1;
	if (philo->table->qtd_philo > 1)
	{
		get_or_leave_fork_two(philo, 1);
		show_info(philo, "has taken a fork\n");
		philo->fork_right = 1;
		show_info(philo, "is eating\n");
		update_data_s_philo(philo);
		usleep(philo->time_to_eat * 1000);
		get_or_leave_fork_two(philo, 0);
		get_or_leave_fork_one(philo, 0);
		show_info(philo, "is sleeping\n");
		usleep(philo->time_to_sleep * 1000);
		show_info(philo, "is thinking\n");
	}
	else
		one_philo(philo, &is_died);
}
