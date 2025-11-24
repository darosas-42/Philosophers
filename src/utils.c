/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:43:24 by dreix             #+#    #+#             */
/*   Updated: 2025/11/24 06:05:00 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	nb;
	int	neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (s[i] == ' ' || s[i] == '\f' || s[i] == '\n' || s[i] == '\r'
		|| s[i] == '\t' || s[i] == '\v')
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			neg = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = (nb * 10) + (s[i] - 48);
		i++;
	}
	return (nb * neg);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}

void	print_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!check_death(philo->data))
		printf("%ld %d %s\n", get_time() - philo->data->start_time, \
philo->id, str);
	pthread_mutex_unlock(&philo->data->print_lock);
}
