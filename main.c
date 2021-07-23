#include"philo.h"
int get_time(struct timeval start)
{
	struct timeval now;
	gettimeofday(&now,0);
	return((now.tv_sec-start.tv_sec)*1000+(now.tv_usec-start.tv_usec)*0.001);

}
void print_msg(t_philo *philo, char *MSG)
{
	printf("|%d| |%d| |%s|\n",get_time(philo->start),philo->number,MSG);
	//usleep(3);
}
void *life(void *argv)
{
	t_philo *philo;

	philo = (t_philo*)argv;
	while(1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo,FORK);
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo,FORK);
		philo->last_meal[1]=EATING;
		print_msg(philo,EAT);
		usleep(philo->t_eat*1000);
		philo->last_meal[1]=CHILLING;
		philo->last_meal[0]=get_time(philo->start);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		//usleep(10);
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
		if(get_time(philo[i]->start)-philo[i]->last_meal[0]>=philo[i]->t_die  && philo[i]->last_meal[1]==CHILLING/*&& pthread_mutex_lock(philo[i]->r_fork) == 0 && pthread_mutex_lock(philo[i]->l_fork)==0*/)
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
				usleep(3);
			}
			i++;
		}
		i = 0;
		while (i<philo[0]->all)
		{
			if(i % 2 != 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				pthread_detach(*(philo[i]->thread));
				usleep(3);
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
