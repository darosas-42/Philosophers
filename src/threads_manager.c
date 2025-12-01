/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 05:54:52 by dreix             #+#    #+#             */
/*   Updated: 2025/11/27 20:21:44 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eat(t_philo *philo, int f_fork, int s_fork)
{
	pthread_mutex_lock(&philo->data->forks[f_fork]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[s_fork]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->data->last_meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->last_meal_lock);
	ft_usleep(philo->data->time_eat, philo->data);
	pthread_mutex_lock(&philo->data->philo_meals);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->data->philo_meals);
	pthread_mutex_unlock(&philo->data->forks[f_fork]);
	pthread_mutex_unlock(&philo->data->forks[s_fork]);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_sleep, philo->data);
	print_status(philo, "is thinking");
	ft_usleep(1, philo->data);
}

static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		f_fork;
	int		s_fork;

	philo = (t_philo *)arg;
	f_fork = philo->left_fork_id;
	s_fork = philo->right_fork_id;
	if (philo->id % 2 == 0)
	{
		f_fork = philo->right_fork_id;
		s_fork = philo->left_fork_id;
	}
	if (philo->id % 2 != 0)
		ft_usleep(5, philo->data);
	while (!check_death(philo->data))
		philo_eat(philo, f_fork, s_fork);
	return (NULL);
}

static void	all_ate_enough(t_arguments *args)
{
	int	i;
	int	meals_eaten_safe;

	i = 0;
	while (args->target_eat > 0 && i < args->nb_philos)
	{
		pthread_mutex_lock(&args->philo_meals);
		meals_eaten_safe = args->philos[i].meals_eaten;
		pthread_mutex_unlock(&args->philo_meals);
		if (meals_eaten_safe < args->target_eat)
			return ;
		i++;
	}
	if (i == args->nb_philos && !check_death(args))
	{
		pthread_mutex_lock(&args->s1died_lock);
		args->someone_died = 1;
		pthread_mutex_unlock(&args->s1died_lock);
	}
}

static void	checker(t_arguments *args)
{
	int		i;
	long	last_meal_safe;
	long	getting_time;

	while (!check_death(args))
	{
		i = -1;
		getting_time = get_time();
		while ((++i < args->nb_philos) && !check_death(args))
		{
			pthread_mutex_lock(&args->last_meal_lock);
			last_meal_safe = args->philos[i].last_meal;
			pthread_mutex_unlock(&args->last_meal_lock);
			if ((getting_time - last_meal_safe) > args->time_die)
			{
				print_status(&args->philos[i], "died");
				pthread_mutex_lock(&args->s1died_lock);
				args->someone_died = 1;
				pthread_mutex_unlock(&args->s1died_lock);
			}
			ft_usleep(1, args);
		}
		all_ate_enough(args);
	}
}

void	handle_pthreads(t_arguments *args)
{
	int			i;

	i = 0;
	args->start_time = get_time();
	while (i < args->nb_philos)
	{
		args->philos[i].last_meal = args->start_time;
		pthread_create(&args->philos[i].thread, NULL, philo_routine, \
&args->philos[i]);
		i++;
	}
	checker(args);
	i = -1;
	while (++i < args->nb_philos)
		pthread_join(args->philos[i].thread, NULL);
}
