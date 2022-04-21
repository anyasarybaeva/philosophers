#include "philo.h"

int	get_time(struct	timeval start)
{
	struct timeval	now;

	gettimeofday(&now, 0);
	return ((now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec - \
	start.tv_usec) * 0.001);
}

void	usleep_new(int	ml)
{
	struct timeval	start;

	gettimeofday(&start, 0);
	while (get_time(start) < ml)
		usleep(2000);
}

void	print_msg(t_philo	*philo, char	*MSG)
{
	pthread_mutex_lock(philo->print);
	printf("%d ms %d %s\n", get_time(philo->start), philo->number, MSG);
	pthread_mutex_unlock(philo->print);
}

void	free_all(t_philo	**philo)
{
	int	i;

	i = -1;
	while (philo[++i])
	{
		pthread_mutex_destroy(philo[i]->r_fork);
		free(philo[i]->r_fork);
	}
	pthread_mutex_destroy(philo[0]->print);
	pthread_mutex_destroy(philo[0]->exit);
	free(philo[0]->print);
	free(philo[0]->exit);
	i = -1;
	while (philo[++i])
	{
		free(philo[i]->thread);
		free(philo[i]);
	}
	free(philo);
}
