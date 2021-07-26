#include"philo.h"
void print_msg(t_philo *philo, char *MSG)
{
	pthread_mutex_lock(philo->print);
	printf("%d %d %s\n",get_time(philo->start),philo->number,MSG);
	pthread_mutex_unlock(philo->print);
}
void check_time_error(t_philo *philo)
{
	int new_error;

	new_error=get_time(philo->start)-(philo->last_meal[0]-philo->t_die+philo->t_eat+philo->t_sleep);
	if(new_error>philo->error[0])
		philo->error[0]=new_error;
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
		philo->last_meal[1]=EATING;
		philo->last_meal[0]=get_time(philo->start)+philo->t_die;
		print_msg(philo,EAT);
		usleep_new(philo->t_eat);
	//	philo->eat[0]+=1;
		philo->last_meal[1]=CHILLING;
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_msg(philo,SLEEP);
		usleep_new(philo->t_sleep);
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
			if((get_time(philo[i].start))>=(philo[i].last_meal[0]) && philo->last_meal[1]==CHILLING)
			{
				pthread_mutex_lock(philo[i].print);
				printf("%d %d %s\n",get_time(philo[i].start),philo[i].number,DIE);
				pthread_mutex_unlock(philo[0].exit);
			}
		}
		usleep(30);
	}
}
void *check_eat(void *argv)
{
	t_philo *philo;
	int i;

	philo = (t_philo*)argv;
	while (1)
	{
		i=-1;
		while (++i<philo[0].all)
		{
			if(philo[i].eat[0]<philo[i].n_eat)
				break;
		}
		if(i==philo[0].all)
		{
			pthread_mutex_lock(philo[i].print);
			usleep(100);
			printf("%d %d %s\n",get_time(philo[0].start),philo[0].number,DIE);
			pthread_mutex_unlock(philo[0].exit);
		}
		i=-1;
		while (++i<philo[0].all)
		{
			if((get_time(philo[i].start))>=(philo[i].last_meal[0]) && philo->last_meal[1]==CHILLING)
			{
				pthread_mutex_lock(philo[i].print);
				printf("%d %d %s\n",get_time(philo[i].start),philo[i].number,DIE);
				pthread_mutex_unlock(philo[0].exit);
			}
		}
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
		if(philo[0]->n_eat!=-1)
			pthread_create(&thread,0,&check_eat,*(philo));
		else
			pthread_create(&thread,0,&check_death,*(philo));
		pthread_detach(thread);
		while (i<philo[0]->all)
		{
			philo[i]->start=philo[0]->start;
			if(i % 2 == 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				pthread_detach(*(philo[i]->thread));
			}
			i++;
		}
		usleep(10);
		i = 0;
		while (i<philo[0]->all)
		{
			if(i % 2 != 0)	
			{
				pthread_create(philo[i]->thread, 0, &life, philo[i]);
				pthread_detach(*(philo[i]->thread));
			}
			i++;
		}
	}
	pthread_mutex_lock(philo[0]->exit);
	return(0);
}
