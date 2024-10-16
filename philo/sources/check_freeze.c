/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_freeze.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:07:43 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/07 16:07:46 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_end_program(t_table *table, t_error *check, int i)
{
	pthread_mutex_lock(&table->philos[i].locker);
	check->finit = (int)(current_timestamp() - (table->philos[i].last_time_eat
				+ 3));
	check->did_eat = table->philos[i].did_eat;
	pthread_mutex_unlock(&table->philos[i].locker);
	pthread_mutex_lock(&table->philos[i].locker);
	check->is_died = table->philos[i].is_died;
	pthread_mutex_unlock(&table->philos[i].locker);
	if (check->is_died)
		return (1);
	if ((check->did_eat >= table->must_eat) && table->must_eat > 0)
		check->eat++;
	if (check->finit > (table->philos->time_to_die))
	{
		pthread_mutex_lock(&table->philos[i].locker);
		table->philos[i].is_died = 1;
		pthread_mutex_unlock(&table->philos[i].locker);
		show_info(&table->philos[i], "died\n");
		pthread_mutex_lock(&table->variable);
		table->stop = 1;
		pthread_mutex_unlock(&table->variable);
		return (1);
	}
	return (0);
}

int	someones_died_or_all_ate(t_table *table)
{
	int		i;
	t_error	check;

	i = -1;
	check.eat = 0;
	while (++i < table->qtd_philo)
	{
		if (check_end_program(table, &check, i))
			return (1);
	}
	if (check.eat >= table->qtd_philo)
	{
		pthread_mutex_lock(&table->variable);
		table->stop = 1;
		pthread_mutex_unlock(&table->variable);
	}
	return (0);
}

int	check_params(int ac, char **str, t_philo *philo, t_table *table)
{
	int	i;

	i = 0;
	while (++i <= ac)
	{
		if (ft_atoi(str[i]) < 1)
			return (0);
	}
	initialize_philos(str, philo, table);
	if (ac == 5 && (ft_atoi(str[5]) > 0))
		return (ft_atoi(str[5]));
	return (-1);
}

void	clean(t_table *table)
{
	int	i;

	i = 0;
	if (table->qtd_philo)
	{
		while (i++ < table->qtd_philo)
		{
			pthread_mutex_destroy(&table->philos[i - 1].fork);
			pthread_mutex_destroy(&table->philos[i - 1].variable);
			pthread_mutex_destroy(&table->philos[i - 1].locker);
		}
		pthread_mutex_destroy(&table->lock);
		pthread_mutex_destroy(&table->variable);
		free(table->philos);
	}
	free(table);
}
