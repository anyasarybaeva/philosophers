#include"philo.h"
void *life(void *argv)
{
	t_philo *philo;
	printf("heree\n");
	philo=(t_philo*)argv;
	printf("philo: %d\n",philo->t_die);
	return(0);
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

void fill_struct(t_philo **philo, int n_of_ph)
{
	int i;

	i = 0;
	//printf("phill struct\n");
	while(++i<n_of_ph)
	{
		philo[i] = malloc(sizeof(t_philo) * (1));
		//printf("phill %d\n",i);
		philo[i]->number=i+1;
		philo[i]->n_eat=philo[0]->n_eat;
		philo[i]->t_sleep=philo[0]->t_sleep;
		philo[i]->t_die=philo[0]->t_die;
		philo[i]->t_eat=philo[0]->n_eat;
		philo[i]->thread = malloc(sizeof(pthread_t));

	}
	philo[n_of_ph]=0;
}

t_philo **init_struct(char **argv)
{
	t_philo	**philo;
	int		n_of_ph;

	//printf("init struct\n");
	n_of_ph = check_number(argv[1]);
//	printf("first arg(number of ph):%d\n",n_of_ph);
	if (n_of_ph < 2 || n_of_ph > 200)
		return (0);
	philo = malloc(sizeof(t_philo*) * (n_of_ph+1));
	philo[0] = malloc(sizeof(t_philo) * (1));
	philo[0]->thread = malloc(sizeof(pthread_t));
	philo[0]->all=n_of_ph;
	philo[0]->t_die = check_number(argv[2]);
	//printf("t_die:%d\n",philo[0].t_die);
	philo[0]->t_eat = check_number(argv[3]);
	//printf("t_eat:%d\n",philo[0].t_eat);
	philo[0]->t_sleep = check_number(argv[4]);
	//printf("t_sleep:%d\n",philo[0].t_sleep);
	philo[0]->n_eat=check_number(argv[5]);
	//printf("n_eat:%d\n",philo[0].n_eat);
	if (philo[0]->t_die == -2 || philo[0]->t_eat == -2 || philo[0]->t_sleep == -2 ||philo[0]->n_eat==-2)
	{
		printf("here\n");
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
			printf("%d\n",philo[i]->t_die);
			if(i % 2 ==0)	
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
			i++;
		}
		i = 0;
		while (i<philo[0]->all)
		{
			if(i % 2 ==0)	
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
			i++;
		}
	}
	return(0);
}