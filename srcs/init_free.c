/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrivka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:17:20 by vrivka            #+#    #+#             */
/*   Updated: 2021/08/10 14:17:22 by vrivka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_philo *philo, t_all *all, int num)
{
	philo->num = num;
	philo->odd = num % 2;
	philo->time_to_die = all->time_to_die * 1000;
	philo->time_to_eat = all->time_to_eat * 1000;
	philo->time_to_sleep = all->time_to_sleep * 1000;
	philo->eat_times = all->eat_times;
	philo->pause = &all->pause;
	philo->print_m = &all->print_m;
	philo->status = &all->status;
	philo->time_start = &all->time_start;
	philo->last_meal_time = 0;
}

static int	init_(t_all *all, char **av)
{
	all->num_philo = my_atoi(av[0]);
	all->time_to_die = my_atoi(av[1]);
	all->time_to_eat = my_atoi(av[2]);
	all->time_to_sleep = my_atoi(av[3]);
	if (av[4])
		all->eat_times = (int)my_atoi(av[4]);
	else
		all->eat_times = -1;
	all->all_eat = 0;
	all->status = ALIVE;
	if (pthread_mutex_init(&all->pause, NULL))
		return (print_error("mutex init failed", NULL));
	if (pthread_mutex_init(&all->print_m, NULL))
	{
		pthread_mutex_destroy(&all->pause);
		return (print_error("mutex init failed", NULL));
	}
	all->philo = malloc(sizeof(t_philo) * all->num_philo);
	if (!all->philo)
	{
		pthread_mutex_destroy(&all->pause);
		pthread_mutex_destroy(&all->print_m);
		return (print_error("cannot allocate memory", NULL));
	}
	return (0);
}

static int	init_forks(t_all *all)
{
	unsigned int	i;

	i = 0;
	while (i < all->num_philo)
	{
		philo_init(&all->philo[i], all, i + 1);
		if (pthread_mutex_init(&all->philo[i].left_fork, NULL))
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&all->philo[i].left_fork);
				free(all->philo);
				pthread_mutex_destroy(&all->pause);
				pthread_mutex_destroy(&all->print_m);
				return (print_error("mutex init failed", NULL));
			}
		}
		i++;
	}
	return (0);
}

int	all_init(t_all *all, char **av)
{
	unsigned int	i;

	if (init_(all, av) || init_forks(all))
		return (1);
	i = 1;
	while (i < all->num_philo)
	{
		all->philo[i].right_fork = &all->philo[i - 1].left_fork;
		i++;
	}
	all->philo[0].right_fork = &all->philo[i - 1].left_fork;
	return (0);
}

void	free_all(t_all *all)
{
	unsigned int	i;

	i = 0;
	while (i < all->num_philo)
	{
		pthread_mutex_destroy(&all->philo[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&all->pause);
	pthread_mutex_destroy(&all->print_m);
	free(all->philo);
	free(all);
}
