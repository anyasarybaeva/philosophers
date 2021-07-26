#include "philo.h"

int	check_number(char	*argv, int	limit_min, int	limit_max)
{
	int	i;

	i = -1;
	if (!argv)
		return (-1);
	while (argv[++i])
	{
		if (!ft_isdigit(argv[i]))
			return (0);
	}
	if (i >= 11)
		return (-2);
	i = ft_atoi(argv);
	if (i < limit_min && i > limit_max)
		i = -2;
	return (i);
}

void	make_forks(int	n_of_ph, t_philo	**philo)
{
	pthread_mutex_t	**forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t *) * n_of_ph);
	while (++i < n_of_ph)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i], 0);
	}
	i = -1;
	while (++i < n_of_ph)
	{	
		philo[i]->r_fork = forks[i];
		philo[i]->l_fork = forks[(i + 1) % n_of_ph];
	}
}

int	fill_philo(t_philo	*philo, char	**argv, pthread_mutex_t	\
	*print,	pthread_mutex_t	*exit)
{
	philo->t_die = check_number(argv[2], 20, 10000);
	philo->t_eat = check_number(argv[3], 20, 10000);
	philo->t_sleep = check_number(argv[4], 20, 10000);
	philo->n_eat = check_number(argv[5], 1, 20);
	philo->thread = malloc(sizeof(pthread_t));
	if (!philo->thread)
		return (0);
	philo->last_meal[0] = philo->t_die;
	philo->last_meal[1] = CHILLING;
	philo->eat[0] = 0;
	philo->print = print;
	philo->exit = exit;
	return (1);
}

t_philo	**fill_struct(int	n_of_ph, char	**argv)
{
	int				i;
	t_philo			**philo;
	pthread_mutex_t	*print;
	pthread_mutex_t	*exit;

	i = -1;
	print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, 0);
	exit = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(exit, 0);
	philo = malloc(sizeof(t_philo *) * (n_of_ph + 1));
	while (++i < n_of_ph)
	{
		philo[i] = malloc(sizeof(t_philo) * (1));
		if (!philo[i])
			return (0);
		philo[i]->number = i + 1;
		philo[i]->all = n_of_ph;
		if (!fill_philo(philo[i], argv, print, exit))
			return (0);
	}
	make_forks(n_of_ph, philo);
	philo[n_of_ph] = 0;
	return (philo);
}

t_philo	**init_struct(char	**argv)
{
	t_philo	**philo;
	int		n_of_ph;

	n_of_ph = check_number(argv[1], 1, 200);
	if (check_number(argv[2], 20, 10000) == -2 || check_number(argv[3], \
	 20, 10000) == -2 || check_number(argv[4], 20, 10000) == -2 \
	 || check_number(argv[5], 20, 10000) == -2 || n_of_ph == -2)
	{
		printf("wrong argvs\n");
		return (0);
	}
	philo = fill_struct(n_of_ph, argv);
	if (!philo)
	{
		printf("malloc error");
		return (0);
	}
	return (philo);
}
