/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:59:21 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/09 16:59:25 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

void	linking_philos(t_table *table, char **str)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(str[1]))
	{
		if ((i + 1) < ft_atoi(str[1]))
		{
			table->philos[i].next = &table->philos[i + 1];
			if (i == 0)
				table->philos[i].prev = &table->philos[ft_atoi(str[1]) - 1];
			else
				table->philos[i].prev = &table->philos[i - 1];
		}
		else
		{
			table->philos[i].next = &table->philos[0];
			table->philos[i].prev = &table->philos[ft_atoi(str[1]) - 2];
		}
	}
}

void	initialize_philos(char **str, t_philo *philo, t_table *table)
{
	int	j;

	j = -1;
	while (++j < ft_atoi(str[1]))
	{
		philo[j].id = j + 1;
		philo[j].is_died = 0;
		philo[j].did_eat = 0;
		philo[j].time_to_die = ft_atoi(str[2]);
		philo[j].time_to_eat = ft_atoi(str[3]);
		philo[j].time_to_sleep = ft_atoi(str[4]);
		philo[j].fork_right = 0;
		philo[j].fork_left = 0;
		philo[j].table = table;
		philo[j].last_time_eat = current_timestamp();
	}
}

void	semaphores_init(t_table *table)
{
	int	i;

	i = -1;
	table->forks = (sem_t *)malloc(sizeof(sem_t) * table->qtd_philo);
	table->philos_pid = (pid_t *)malloc(sizeof(pid_t) * table->qtd_philo);
	while (++i < table->qtd_philo)
	{
		sem_init(&table->forks[i], 1, 1);
		sem_init(&table->philos[i].variable, 1, 1);
	}
	sem_init(&table->variable, 1, 1);
}

// void	create_death_check(t_table *table)
// {
// 	pthread_create(&table->thread, NULL, death, table);
// 	pthread_join(table->thread, NULL);
// }
