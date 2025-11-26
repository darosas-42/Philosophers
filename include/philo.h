/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:47:55 by dreix             #+#    #+#             */
/*   Updated: 2025/11/26 03:32:01 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					meals_eaten;
	long				last_meal;
	int					left_fork_id;
	int					right_fork_id;
	struct s_arguments	*data;
}	t_philo;

typedef struct s_arguments
{
	int				nb_philos;
	long			time_die;
	long			time_eat;
	long			time_sleep;
	int				target_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	last_meal_lock;
	pthread_mutex_t	philo_meals;
	pthread_mutex_t	s1died_lock;
	int				someone_died;
	t_philo			*philos;
}	t_arguments;

enum	e_errors
{
	NOT_DIGIT = 1,
	BAD_AGV = 2,
	AMT_AGV = 3,
	MUTEX = 4,
	MALLOC = 5
};

int		error_philo(int err_type);
int		init_struct(t_arguments *args, char **argv);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);
long	get_time(void);
void	ft_usleep(long milliseconds, t_arguments *args);
void	print_status(t_philo *philo, char *str);
void	cleanup(t_arguments *args);
void	cleanup_forks(t_arguments *args);
int		check_death(t_arguments *args);
void	handle_pthreads(t_arguments *args);
void	handle_one_pthread(t_arguments *args);

#endif