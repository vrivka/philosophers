#include "philo.h"

int	check_arg(const char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

size_t	my_atoi(const char *str)
{
	size_t	i;
	size_t	result;
	int		sign;

	result = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

int check_args(int ac, char **av)
{
	long int value;
	size_t len;
	int i;

	if (ac < 4 || ac > 5)
		return (print_error("wrong number of arguments", NULL));
	i = 0;
	while (av[i])
	{
		len = my_strlen(av[i]);
		if (check_arg(av[i]))
			return (print_error("wrong argument", av[i]));
		if (len > 10)
			return (print_error("argument out of range", av[i]));
		value = (long int)my_atoi(av[i]);
		if (value <= 0 || value > 4294967295)
			return (print_error("argument out of range", av[i]));
		i++;
	}
	return (0);
}
