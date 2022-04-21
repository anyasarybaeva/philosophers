#include"philo.h"

void	*life(void	*argv)
{
	t_philo	*philo;

	philo = (t_philo *)argv;
	while (1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo, FORK);
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo, FORK);
		philo->last_meal[1] = EATING;
		philo->last_meal[0] = get_time(philo->start) + philo->t_die;
		print_msg(philo, EAT);
		usleep_new(philo->t_eat);
		philo->eat[0] += 1;
		philo->last_meal[1] = CHILLING;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_msg(philo, SLEEP);
		usleep_new(philo->t_sleep);
		print_msg(philo, THINK);
	}
	return (0);
}

void	philo_lounge(t_philo	**philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->all)
	{
		philo[i]->start = philo[0]->start;
		if (i % 2 == 0)
		{
			pthread_create(philo[i]->thread, 0, &life, philo[i]);
			pthread_detach(*(philo[i]->thread));
		}
	}
	usleep(100);
	i = -1;
	while (++i < philo[0]->all)
	{
		if (i % 2 != 0)
		{
			pthread_create(philo[i]->thread, 0, &life, philo[i]);
			pthread_detach(*(philo[i]->thread));
		}
	}
}

int	main(int	argc, char	**argv)
{
	t_philo		**philo;
	int			i;
	pthread_t	thread;

	i = -1;
	if (argc > 6 || argc < 5)
		printf("Wrong number of arg");
	else
	{
		philo = init_struct(argv);
		if (!philo)
			return (0);
		gettimeofday(&(philo[0]->start), 0);
		pthread_mutex_lock(philo[0]->exit);
		pthread_create(&thread, 0, &check_death, *(philo));
		pthread_detach(thread);
		philo_lounge(philo);
		pthread_mutex_lock(philo[0]->exit);
		free_all(philo);
	}
	return (0);
}
