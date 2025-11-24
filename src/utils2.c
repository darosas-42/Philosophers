/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 06:01:21 by dreix             #+#    #+#             */
/*   Updated: 2025/11/24 06:05:32 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_arguments *args)
{
	int	died;

	pthread_mutex_lock(&args->s1died_lock);
	died = args->someone_died;
	pthread_mutex_unlock(&args->s1died_lock);
	return (died);
}

void	cleanup_forks(t_arguments *args)
{
	int	i;

	if (args->forks)
	{
		i = -1;
		while (++i < args->nb_philos)
			pthread_mutex_destroy(&args->forks[i]);
		free(args->forks);
		args->forks = NULL;
	}
}

void	cleanup(t_arguments *args)
{
	cleanup_forks(args);
	pthread_mutex_destroy(&args->print_lock);
	pthread_mutex_destroy(&args->last_meal_lock);
	pthread_mutex_destroy(&args->s1died_lock);
	pthread_mutex_destroy(&args->philo_meals);
	if (args->philos)
		free(args->philos);
}
