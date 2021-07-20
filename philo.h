#ifndef PHILO_H
# define PHILO_H
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
#define FORK " has taken a fork\n"
#define EAT " is eating\n"
#define SLEEP " is sleeping\n"
#define THINK " is thinking\n"
#define DIE " died\n"
typedef struct s_philo
{
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork; 
	int all;
	int number;
	int t_eat;
	int t_sleep;
	int t_die;
	int n_eat;
	pthread_t		*thread;

}				t_philo;
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
void	ft_putstr(char *s);
void	ft_putnbr_fd(int n, int fd);
#endif