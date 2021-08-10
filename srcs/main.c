#include "philo.h"

static void eat_counter(t_all *all)
{
	unsigned int i;

	while (all->status == ALIVE)
	{
		i = 0;
		while (i < all->num_philo)
		{
			if (all->philo[i].eat_times == 0)
			{
				all->all_eat++;
				all->philo[i].eat_times--;
			}
			i++;
		}
		if (all->all_eat == all->num_philo)
			all->status = DONE;
	}
}

static void philo_wait(t_all *all)
{
	unsigned int i;

	i = 0;
	while (i < all->num_philo)
	{
		pthread_join(all->philo[i].monitor, NULL);
		i++;
	}
}

static int create_threads(t_all *all)
{
	unsigned int i;

	i = 0;
	while (i < all->num_philo)
	{
		if (pthread_create(&all->philo[i].philo, NULL,
			&philo_thread, &all->philo[i]))
		{
			all->status = ERROR;
			return (print_error("cannot create a thread", NULL));
		}
		if (pthread_create(&all->philo[i].monitor, NULL, &philo_monitor,
			&all->philo[i]))
		{
			all->status = ERROR;
			return (print_error("cannot create a thread", NULL));
		}
		i++;
	}
	all->time_start = get_time();
	return (0);
}

static int start_philo(t_all *all)
{
	int ret;

	pthread_mutex_lock(&all->pause);
	ret = create_threads(all);
	pthread_mutex_unlock(&all->pause);
	if (all->eat_times > 0)
		eat_counter(all);
	philo_wait(all);
	return (ret);
}

int main(int ac, char **av)
{
	t_all *all;

	if (check_args(ac - 1, &av[1]))
		return (1);
	all = malloc(sizeof(t_all));
	if (all_init(all, &av[1]))
		return (1);
	if (start_philo(all))
	{
		free_all(all);
		return (1);
	}
	free_all(all);
	return 0;
}
