/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquissan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:56:43 by aquissan          #+#    #+#             */
/*   Updated: 2024/10/11 15:56:46 by aquissan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H
# include <pthread.h>
# include <semaphore.h>
# include <stdatomic.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	int					time_to_eat;
	int					time_to_sleep;
	int					time_to_die;
	int					time_to_thing;
	int					is_died;
	int					did_eat;
	unsigned long		last_time_eat;
	int					fork_right;
	int					fork_left;
	t_table				*table;
	sem_t				variable;
	pid_t				philosopher;
	t_philo				*next;
	t_philo				*prev;
}						t_philo;

typedef struct s_table
{
	t_philo				*philos;
	pid_t				*philos_pid;
	pid_t				main_pid;
	sem_t				*forks;
	sem_t				variable;
	int					must_eat;
	unsigned long		time;
	int					qtd_philo;
	int					stop;
}						t_table;

typedef struct s_error
{
	int					eat;
	int					finit;
	int					did_eat;
	int					is_died;
}						t_error;

// Check
int						check_params(int ac, char **str, t_philo *philo,
							t_table *table);
void					clean(t_table *table);
void					*death(void *philos);
int						check_end_program(t_table *table, t_error *check,
							int i);
int						there_was_an_error(t_table *table, char **argv,
							int argc);

// Philos
void					linking_philos(t_table *table, char **str);
void					initialize_philos(char **str, t_philo *philo,
							t_table *table);
void					create_death_check(t_table *table);
void					runs(t_philo *philo);
void					*philosopher_day(void *philosopher);
void					philosophers_problem(t_table *table);
void					semaphores_init(t_table *table);

// Info
void					show_info(t_philo *philo, char *info);
void					update_data_s_philo(t_philo *philo);

// Forks
void					get_or_leave_fork_one(t_philo *philo, int action);
void					get_or_leave_fork_two(t_philo *philo, int action);

// UTILS
unsigned long			current_timestamp(void);
int						ft_putstr_fd(char *str, int fd);
int						ft_atoi(char *nptr);
int						someones_died_or_all_ate(t_table *table);
void					create_death_check(t_table *table);
#endif