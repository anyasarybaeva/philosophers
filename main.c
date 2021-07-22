#include"philo.h"
int get_time(struct timeval start)
{
	struct timeval now;
	gettimeofday(&now,0);
	return((now.tv_sec-start.tv_sec)*1000+(now.tv_usec-start.tv_usec)*0.001);

}
/*void print_msg(t_philo *philo, int MSG)
{
	ft_putnbr(get_time(philo->start));
	ft_putstr(" ");
	ft_putnbr(philo->number);
	if(MSG==F)
		ft_putstr(FORK);
	else if(MSG==E)
		ft_putstr(EAT);
	else if(MSG==S)
		ft_putstr(SLEEP);
	else if(MSG==T)
		ft_putstr(THINK);
	else if(MSG==D)
		ft_putstr(DIE);
	//usleep(10);
}*/
void print_msg(t_philo *philo, char *MSG)
{
	printf("|%d| |%d| |%s|\n",get_time(philo->start),philo->number,MSG);
	usleep(3);
	/*if(MSG==F)
		printf("%s",FORK);
	else if(MSG==E)
		printf("%s",EAT);
	else if(MSG==S)
		printf("%s",SLEEP);
	else if(MSG==T)
		printf("%s",THINK);
	else if(MSG==D)
		printf("%s",DIE);*/
	//usleep(10);
}
void *life(void *argv)
{
	t_philo *philo;

	philo = (t_philo*)argv;
	while(1)
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		philo->last_meal[1]=EATING;
		print_msg(philo,FORK);
		print_msg(philo,FORK);
		print_msg(philo,EAT);
		usleep(philo->t_eat*1000);
		philo->last_meal[0]=get_time(philo->start);
		philo->last_meal[1]=CHILLING;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		usleep(10);
		print_msg(philo,SLEEP);
		usleep(philo->t_sleep*1000);
		print_msg(philo,THINK);
	}
	return (0);
}

int check_death(t_philo **philo)
{
	int i;
	
	i=-1;
	while (philo[++i])
	{
		//printf("check_death:%d\n",(get_time(philo[i]->start)-philo[i]->last_meal[0])-philo[i]->t_die);
		if(get_time(philo[i]->start)-philo[i]->last_meal[0]>=philo[i]->t_die)
		{
			print_msg(philo[i],DIE);
			//free_all(philo);
			return(1);
		}
	}
	usleep(3);
	return(0);
}
int main(int argc,char **argv)
{
	t_philo **philo;
	int		i;
	int time;

	i = 0;
	if (argc > 6 || argc < 5)
	{	
		printf("Wrong number of arg");
		return(0);
	}
	else
	{
		philo = init_struct(argv);
		if (!philo)
			return(0);
		gettimeofday(&(philo[0]->start),0);
		while (i<philo[0]->all)
		{
			philo[i]->start=philo[0]->start;
			if(i % 2 == 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				pthread_detach(*(philo[i]->thread));
				usleep(100);
			}
			i++;
		}
		i = 0;
		usleep(100);
		while (i<philo[0]->all)
		{
			if(i % 2 != 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				pthread_detach(*(philo[i]->thread));
				usleep(100);
			}
			i++;
		}
	}
	while(1)
	{
		if(check_death(philo))
			break;
	};
	return(0);
}
