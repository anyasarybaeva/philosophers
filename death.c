#include"philo.h"

void	hungry_death(t_philo	*philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].all)
	{
		if (get_time(philo[i].start) >= philo[i].last_meal[0] && \
		philo->last_meal[1] == CHILLING)
		{
			pthread_mutex_lock(philo[i].print);
			printf("%d %d %s\n", get_time(philo[i].start), philo[i].number, DIE);
			pthread_mutex_unlock(philo[0].exit);
		}
	}
}

void	*check_death(void	*argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	if (philo[0].n_eat == -1)
	{
		while (1)
		{
			hungry_death(philo);
			usleep(30);
		}
	}
	while (1)
	{
		if (!check_eat(philo))
			hungry_death(philo);
	}
}

int	check_eat(t_philo	*philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].all)
	{
		if (philo[i].eat[0] < philo[i].n_eat)
			break ;
	}
	if (i == philo[0].all)
	{
		pthread_mutex_lock(philo[0].print);
		printf("%d %d %s\n", get_time(philo[0].start), philo[0].number, DIE);
		pthread_mutex_unlock(philo[0].exit);
		return (1);
	}
	return (0);
}
