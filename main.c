#include"philo.h"
void print_msg(t_philo *philo, char *MSG)
{
	pthread_mutex_lock(philo->print);
	printf("|%d| |%d| |%s|\n",get_time(philo->start),philo->number,MSG);
	pthread_mutex_unlock(philo->print);
}
void *life(void *argv)
{
	t_philo *philo;

	philo = (t_philo*)argv;
	philo->last_meal[0]=philo->t_die;
	
	while(1)
	{
		pthread_mutex_lock(philo->r_fork);
		print_msg(philo,FORK);
		pthread_mutex_lock(philo->l_fork);
		print_msg(philo,FORK);
		philo->last_meal[0]=get_time(philo->start)+philo->t_die;
		print_msg(philo,EAT);
		usleep(philo->t_eat*1000);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_msg(philo,SLEEP);
		usleep(philo->t_sleep*1000);
		print_msg(philo,THINK);
	}
	return (0);
}

void *check_death(void *argv)
{
	int i;
	t_philo *philo;
	philo = (t_philo*)argv;
	while(1)
	{
		i=-1;
		while (++i<philo[0].all)
		{
			//printf("%d %d %d\n",get_time(philo[i].start),philo[i].last_meal[0]+philo[i].t_die, i);
			if(get_time(philo[i].start)>(philo[i].last_meal[0]))
			{
				pthread_mutex_lock(philo[i].print);
				//free_all()
				printf("|%d| |%d| |%s| %d\n",get_time(philo[i].start),philo[i].number,DIE,philo[i].last_meal[0]);
				pthread_mutex_unlock(philo[i].exit);
			}
		}
		usleep(30);
	}
}
int main(int argc,char **argv)
{
	t_philo **philo;
	int		i;
	int time;
	pthread_t thread;

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
		pthread_mutex_lock(philo[0]->exit);
		pthread_create(&thread,0,&check_death,*(philo));
		pthread_detach(thread);
		while (i<philo[0]->all)
		{
			philo[i]->start=philo[0]->start;
			if(i % 2 == 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				pthread_detach(*(philo[i]->thread));
				//usleep(10);
			}
			i++;
		}
		usleep(20);
		i = 0;
		while (i<philo[0]->all)
		{
			if(i % 2 != 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				pthread_detach(*(philo[i]->thread));
				//usleep(10);
			}
			i++;
		}
	}
	pthread_mutex_lock(philo[0]->exit);
	//free_all()
	return(0);
}
