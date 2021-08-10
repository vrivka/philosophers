/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:16:42 by vrivka            #+#    #+#             */
/*   Updated: 2021/08/10 14:39:43 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	my_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	print_error(char *error_string, const char *arg)
{
	write(STDERR, PROGRAM_NAME, my_strlen(PROGRAM_NAME));
	write(STDERR, ": ", 2);
	if (!arg)
		write(STDERR, error_string, my_strlen(error_string));
	else
	{
		write(STDERR, arg, my_strlen(arg));
		write(STDERR, ": ", 2);
		write(STDERR, error_string, my_strlen(error_string));
	}
	write(STDERR, "\n", 1);
	return (1);
}

long	get_time(void)
{
	struct timeval	elapsed_time;

	gettimeofday(&elapsed_time, NULL);
	return (elapsed_time.tv_sec * 1000000 + elapsed_time.tv_usec);
}

void	my_usleep(long time)
{
	long	stop;

	stop = get_time() + time;
	while (get_time() <= stop)
		usleep(10);
}

void	print_massage(long timestamp, char *massage, t_philo *philo)
{
	pthread_mutex_lock(philo->print_m);
	if (*philo->status == ALIVE)
		printf("%ld %d %s\n", timestamp, philo->num, massage);
	pthread_mutex_unlock(philo->print_m);
}
