/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:59 by vrivka            #+#    #+#             */
/*   Updated: 2021/08/10 14:38:33 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_monitor(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->pause);
	pthread_mutex_unlock(philo->pause);
	philo->last_meal_time = get_time();
	while (*philo->status == ALIVE && (philo->last_meal_time
			+ philo->time_to_die - get_time()) / 1000 >= 0)
		my_usleep(100);
	if (*philo->status == ALIVE)
		*philo->status = DEAD_M;
	pthread_mutex_lock(philo->print_m);
	if (*philo->status == DEAD_M)
	{
		printf("%ld %d %s\n", (get_time() - *philo->time_start) / 1000,
			   philo->num, IS_DEAD);
		*philo->status = DEAD;
	}
	pthread_mutex_unlock(philo->print_m);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_join(philo->philo, NULL);
	return (NULL);
}
