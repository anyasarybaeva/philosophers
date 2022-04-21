#ifndef PHILO_H
# define PHILO_H
# include<unistd.h>
# include<pthread.h>
# include<string.h>
# include<stdio.h>
# include<stdlib.h>
# include <sys/time.h>
# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define EATING 6
# define CHILLING 7

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*exit;
	struct timeval	start;
	int				all;
	int				number;
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				eat[1];
	int				n_eat;
	int				last_meal[2];
	int				error[1];
	pthread_t		*thread;
}					t_philo;
int					ft_isdigit(int	c);
int					ft_atoi(const char	*str);
t_philo				**init_struct(char	**argv);
void				free_all(t_philo	**philo);
void				usleep_new(int	ml);
int					get_time(struct timeval	start);
void				print_msg(t_philo	*philo, char	*MSG);
void				*life(void	*argv);
void				hungry_death(t_philo	*philo);
void				*check_death(void	*argv);
int					check_eat(t_philo	*philo);
#endif
