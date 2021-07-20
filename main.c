#include"philo.h"
long long int get_time()
{
	struct timeval c_time;
	
	gettimeofday(&c_time,0);
	return(c_time.tv_usec);
}
void *life(void *argv)
{
	t_philo *philo;
	long long int last_meal;

	philo = (t_philo*)argv;
	while(1)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		printf("%lld %d %s",get_time(),philo->number,FORK);
		printf("%lld %d %s",get_time(),philo->number,FORK);
		printf("%lld %d %s",get_time(),philo->number,EAT);
		usleep(philo->t_eat*1000);
		last_meal=get_time();
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		printf("timestamp_in_ms %d %s",philo->number,SLEEP);
		usleep(philo->t_sleep*1000);
		if(last_meal-get_time()>=philo->t_die)
		{
			printf("%lld %d %s",get_time(),philo->number,DIE);
			return(0);
		}
		printf("%lld %d %s",get_time(),philo->number,THINK);
		if(last_meal-get_time()>=philo->t_die)
		{
			printf("%lld %d %s",get_time(),philo->number,DIE);
			return(0);
		}
	}
//	printf("philo: %d\n", philo->number);
	return (0);
}

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
		forks[i]=malloc(sizeof(pthread_mutex_t));
	i=-1;
	while(++i<n_of_ph)
	{	
		pthread_mutex_init(forks[i],0);
		philo[i]->r_fork = forks[i];
		philo[i]->l_fork = forks[(i+1)%n_of_ph];
	}
}
void fill_struct(t_philo **philo, int n_of_ph)
{
	int i;
	
	i = 0;
	while(++i<n_of_ph)
	{
		philo[i] = malloc(sizeof(t_philo) * (1));
		if(!philo[i])
			return;
		philo[i]->number=i+1;
		philo[i]->n_eat=philo[0]->n_eat;
		philo[i]->t_sleep=philo[0]->t_sleep;
		philo[i]->t_die=philo[0]->t_die;
		philo[i]->t_eat=philo[0]->n_eat;
		philo[i]->thread = malloc(sizeof(pthread_t));
		if(!philo[i]->thread)
			return;
	}
	make_forks(n_of_ph,philo);
	philo[n_of_ph] = 0;
}

t_philo **init_struct(char **argv)
{
	t_philo	**philo;
	int		n_of_ph;

	n_of_ph = check_number(argv[1]);
	if (n_of_ph < 2 || n_of_ph > 200)
		return (0);
	philo = malloc(sizeof(t_philo*) * (n_of_ph+1));
	philo[0] = malloc(sizeof(t_philo) * (1));
	philo[0]->thread = malloc(sizeof(pthread_t));
	philo[0]->all=n_of_ph;
	philo[0]->t_die = check_number(argv[2]);
	philo[0]->t_eat = check_number(argv[3]);
	philo[0]->t_sleep = check_number(argv[4]);
	philo[0]->n_eat=check_number(argv[5]);
	if (philo[0]->t_die == -2 || philo[0]->t_eat == -2 || philo[0]->t_sleep == -2 ||philo[0]->n_eat==-2)
	{
		free(philo);
		return(0);
	}
	fill_struct(philo, n_of_ph);
	return(philo);
}

int main(int argc,char **argv)
{
	t_philo **philo;
	int		i;

	i = 0;
	if (argc > 6 || argc < 5)
		printf("Wrong number of arg");
	else
	{
		philo = init_struct(argv);
		if (!philo)
			printf("Wrong type of arg");
		while (i<philo[0]->all)
		{
			if(i % 2 == 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				usleep(10);
			}
			i++;
		}
		i = 0;
		while (i<philo[0]->all)
		{
			if(i % 2 != 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				usleep(10);
			}
			i++;
		}
	}
	return(0);
}