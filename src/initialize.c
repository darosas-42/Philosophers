/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 05:48:55 by dreix             #+#    #+#             */
/*   Updated: 2025/11/27 20:21:35 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(t_arguments *args, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (error_philo(NOT_DIGIT));
		}
	}
	if (args->nb_philos < 1 || args->time_die < 0 || args->time_eat < 0
		|| args->time_sleep < 0)
		return (error_philo(BAD_AGV));
	return (1);
}

static int	init_other_mutexes(t_arguments *args)
{
	if (pthread_mutex_init(&args->print_lock, NULL) != 0)
		return (cleanup_forks(args), error_philo(MUTEX));
	if (pthread_mutex_init(&args->last_meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&args->print_lock);
		return (cleanup_forks(args), error_philo(MUTEX));
	}
	if (pthread_mutex_init(&args->philo_meals, NULL) != 0)
	{
		pthread_mutex_destroy(&args->last_meal_lock);
		pthread_mutex_destroy(&args->print_lock);
		return (cleanup_forks(args), error_philo(MUTEX));
	}
	if (pthread_mutex_init(&args->s1died_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&args->philo_meals);
		pthread_mutex_destroy(&args->last_meal_lock);
		pthread_mutex_destroy(&args->print_lock);
		return (cleanup_forks(args), error_philo(MUTEX));
	}
	return (1);
}

static int	init_mutexes(t_arguments *args)
{
	int	i;

	args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_philos);
	if (!args->forks)
		return (error_philo(MALLOC));
	i = 0;
	while (i < args->nb_philos)
	{
		if (pthread_mutex_init(&args->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&args->forks[i]);
			free(args->forks);
			return (error_philo(MUTEX));
		}
		i++;
	}
	return (init_other_mutexes(args));
}

static int	init_philosophers(t_arguments *args)
{
	int	i;

	args->philos = malloc(sizeof(t_philo) * args->nb_philos);
	if (!args->philos)
		return (error_philo(MALLOC));
	i = 0;
	while (i < args->nb_philos)
	{
		args->philos[i].id = i + 1;
		args->philos[i].meals_eaten = 0;
		args->philos[i].left_fork_id = i;
		args->philos[i].right_fork_id = (i + 1) % args->nb_philos;
		args->philos[i].data = args;
		i++;
	}
	return (1);
}

int	init_struct(t_arguments *args, char **argv)
{
	args->nb_philos = ft_atoi(argv[1]);
	args->time_die = ft_atoi(argv[2]);
	args->time_eat = ft_atoi(argv[3]);
	args->time_sleep = ft_atoi(argv[4]);
	args->target_eat = 0;
	args->someone_died = 0;
	if (argv[5])
	{
		args->target_eat = ft_atoi(argv[5]);
		if (args->target_eat <= 0)
			return (error_philo(BAD_AGV));
	}
	if (!check_args(args, argv))
		return (0);
	if (!init_mutexes(args))
		return (0);
	if (!init_philosophers(args))
		return (0);
	return (1);
}
