/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:06:09 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/09 17:06:12 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers_bonus.h"

// void	get_or_leave_fork_one(t_philo *philo, int action)
// {
// 	if (action)
// 	{
// 		if ((philo->id % 2))
// 			// pthread_mutex_lock(&philo->next->fork);
// 		else
// 			// pthread_mutex_lock(&philo->fork);
// 		philo->fork_left = 1;
// 	}
// 	else
// 	{
// 		if (!philo->fork_left)
// 			return ;
// 		if ((philo->id % 2))
// 			// pthread_mutex_unlock(&philo->next->fork);
// 		else
// 			// pthread_mutex_unlock(&philo->fork);
// 		philo->fork_left = 0;
// 	}
// }

// void	get_or_leave_fork_two(t_philo *philo, int action)
// {
// 	if (action)
// 	{
// 		if (!philo->fork_left)
// 			return ;
// 		if ((philo->id % 2) && (philo->fork_left || philo->fork_right))
// 			// pthread_mutex_lock(&philo->fork);
// 		else
// 			// pthread_mutex_lock(&philo->next->fork);
// 		philo->fork_right = 1;
// 	}
// 	else
// 	{
// 		if (!philo->fork_right)
// 			return ;
// 		if ((philo->id % 2) && (philo->fork_left || philo->fork_right))
// 			// pthread_mutex_unlock(&philo->fork);
// 		else
// 			// pthread_mutex_unlock(&philo->next->fork);
// 		philo->fork_right = 0;
// 	}
// }
