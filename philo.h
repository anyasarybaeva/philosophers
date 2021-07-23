#ifndef PHILO_H
# define PHILO_H
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "died"
#define F 1
#define E 2
#define S 3
#define T 4
#define D 5
#define EATING 6
#define CHILLING 7

typedef struct s_philo
{
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
	struct timeval start; 
	int all;
	int number;
	int t_eat;
	int t_sleep;
	int t_die;
	int n_eat;
	int last_meal[2];
	pthread_t		*thread;

}				t_philo;
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
t_philo **init_struct(char **argv);
void free_all(t_philo **philo);
#endif