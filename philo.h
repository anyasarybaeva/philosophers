#ifndef PHILO_H
# define PHILO_H
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct s_philo
{
	int number;
	int t_eat;
	int t_sleep;
	int t_die;
	int n_eat;
	pthread_t		*thread;

}				t_philo;
int	ft_isdigit(int c);
int	ft_atoi(const char *str);

#endif