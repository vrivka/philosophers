#include "philo.h"

static void take_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_massage((get_time() - *philo->time_start) / 1000, TAKE_RFORK, philo);
	pthread_mutex_lock(&philo->left_fork);
	print_massage((get_time() - *philo->time_start) / 1000, TAKE_LFORK, philo);
}

static void drop_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
}

static void eat(t_philo *philo)
{
	philo->last_meal_time = get_time();
	print_massage((philo->last_meal_time - *philo->time_start) / 1000,
		START_EAT, philo);
	my_usleep(philo->time_to_eat);
	if (philo->eat_times > 0)
		philo->eat_times--;
}

static void sleep_think(t_philo *philo)
{
	print_massage((get_time() - *philo->time_start) / 1000, START_SLEEP, philo);
	my_usleep(philo->time_to_sleep);
	print_massage((get_time() - *philo->time_start) / 1000, START_THINK, philo);
}

void *philo_thread(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;
	pthread_mutex_lock(philo->pause);
	pthread_mutex_unlock(philo->pause);
	if (!philo->odd)
		my_usleep(1000);
	while (*philo->status == ALIVE)
	{
		take_fork(philo);
		eat(philo);
		drop_fork(philo);
		sleep_think(philo);
	}
	return (NULL);
}
