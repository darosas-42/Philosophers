/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dreix <darosas-@student.42malaga.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 17:43:29 by dreix             #+#    #+#             */
/*   Updated: 2025/11/24 06:03:07 by dreix            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_philo(int err_type)
{
	if (err_type == NOT_DIGIT)
		printf("Error: numeric parameters required.\n");
	else if (err_type == BAD_AGV)
		printf("Error: philosophers > 1 and \
positive numeric parameters required.\n");
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
	handle_pthreads(&args);
	cleanup(&args);
	return (0);
}
