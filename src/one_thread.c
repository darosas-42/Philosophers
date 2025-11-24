/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_thread.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:44:05 by darosas-          #+#    #+#             */
/*   Updated: 2025/11/24 19:57:57 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->forks[0]);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_die + 1, philo->data);
	print_status(philo, "died");
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (NULL);
}

void	handle_one_pthread(t_arguments *args)
{
	args->philos[0].last_meal = get_time();
	pthread_create(&args->philos[0].thread, NULL, one_philo, \
&args->philos[0]);
	pthread_join(args->philos[0].thread, NULL);
}
