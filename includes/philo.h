#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define PROGRAM_NAME "philo"
#define TAKE_LFORK "has taken a left fork"
#define TAKE_RFORK "has taken a right fork"
#define START_EAT "is eating"
#define START_SLEEP "is sleeping"
#define START_THINK "is thinking"
#define IS_DEAD "died"
#define ERROR -1
#define ALIVE 1
#define DEAD 0
#define DONE 0
#define DEAD_M 2
#define STDERR 2

typedef struct s_philo
{
	pthread_mutex_t *pause;
	pthread_mutex_t *print_m;
	pthread_mutex_t left_fork;
	pthread_mutex_t *right_fork;
	pthread_t philo;
	pthread_t monitor;
	long *time_start;
	int *status;
	int odd;
	unsigned int num;
	unsigned int time_to_die;
	unsigned int time_to_eat;
	unsigned int time_to_sleep;
	int eat_times;
	long last_meal_time;
} t_philo;

typedef struct s_all
{
	unsigned int num_philo;
	unsigned int time_to_die;
	unsigned int time_to_eat;
	unsigned int time_to_sleep;
	int eat_times;
	unsigned int all_eat;
	int status;
	long time_start;
	pthread_mutex_t pause;
	pthread_mutex_t print_m;
	t_philo *philo;
} t_all;


int check_args(int ac, char **av);
int all_init(t_all *all, char **av);
void *philo_thread(void *ptr);
void *philo_monitor(void *ptr);
void free_all(t_all *all);
size_t	my_atoi(const char *str);
size_t my_strlen(char const *str);
long get_time(void);
void my_usleep(long time);
void print_massage(long timestamp, char *massage, t_philo *philo);
int print_error(char *error_string, const char *arg);

#endif
