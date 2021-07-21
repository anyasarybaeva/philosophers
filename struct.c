#include "philo.h"

int check_number(char *argv)
{
	int i;

	i = -1;
	if(!argv)
		return(-1);
	while (argv[++i])
	{
		if (!ft_isdigit(argv[i]))
			return(0);
	}
	i=ft_atoi(argv);
	if(i < 1)
		i = -2;
	return(i);
}

void make_forks(int n_of_ph,t_philo **philo)
{
	pthread_mutex_t **forks;
	int i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t*)*n_of_ph);
	while (++i<n_of_ph)
	{
		forks[i]=malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(forks[i],0);
	}
	i=-1;
	while(++i<n_of_ph)
	{	
		philo[i]->r_fork = forks[i];
		philo[i]->l_fork = forks[(i+1)%n_of_ph];
	}
}
t_philo **fill_struct(int n_of_ph, char **argv)
{
	int i;
	t_philo **philo;
	i = -1;

	philo=malloc(sizeof(t_philo*)*(n_of_ph+1));
	while(++i<n_of_ph)
	{
		philo[i] = malloc(sizeof(t_philo) * (1));
		if(!philo[i])
			return(0);
		philo[i]->number=i+1;
		philo[i]->n_eat=check_number(argv[5]);
		philo[i]->t_sleep=check_number(argv[4]);
		philo[i]->t_die=check_number(argv[2]);
		philo[i]->t_eat=check_number(argv[3]);
		philo[i]->thread = malloc(sizeof(pthread_t));
		if(!philo[i]->thread)
			return(0);
		philo[i]->last_meal=malloc(sizeof(int)*2);
		philo[i]->last_meal[0]=-1;
		philo[i]->last_meal[1]=CHILLING;
		philo[i]->all=n_of_ph;
		//philo[i]->
	}
	make_forks(n_of_ph,philo);
	philo[n_of_ph] = 0;
	return(philo);
}

t_philo **init_struct(char **argv)
{
	t_philo	**philo;
	int		n_of_ph;

	n_of_ph = check_number(argv[1]);
	if (n_of_ph < 2 || n_of_ph > 200)
		return (0);
	//philo = malloc(sizeof(t_philo*) * (n_of_ph+1));
	if (check_number(argv[2]) == -2 || check_number(argv[3]) == -2 ||  check_number(argv[4]) == -2 ||check_number(argv[5]))
	{
		//free(philo);
		return(0);
	}
	return(fill_struct(n_of_ph,argv));
	//return(philo);
}