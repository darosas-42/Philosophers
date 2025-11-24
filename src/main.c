/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darosas- <darosas-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:29 by dreix             #+#    #+#             */
/*   Updated: 2025/11/24 19:56:20 by darosas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_philo(int err_type)
{
	if (err_type == NOT_DIGIT)
		printf("Error: numeric parameters required.\n");
	else if (err_type == BAD_AGV)
		printf("Error: positive numeric parameters required.\n");
	else if (err_type == AMT_AGV)
		printf("Error: wrong amount of arguments.\n");
	else if (err_type == MUTEX)
		printf("Error: mutex initialization failed.\n");
	else if (err_type == MALLOC)
		printf("Error: no memory left in device for malloc.\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_arguments	args;

	if (argc < 5 || argc > 6)
	{
		error_philo(AMT_AGV);
		return (1);
	}
	args.start_time = get_time();
	if (!init_struct(&args, argv))
		return (1);
	if (args.nb_philos == 1)
		handle_one_pthread(&args);
	else
		handle_pthreads(&args);
	cleanup(&args);
	return (0);
}
