#include "philo.h"
int get_time(struct timeval start)
{
	struct timeval now;
	gettimeofday(&now,0);
	return((now.tv_sec-start.tv_sec)*1000+(now.tv_usec-start.tv_usec)*0.001);
}
int get_now()
{
	struct timeval time;
	int now;

	gettimeofday(&time,0);
	now=time.tv_sec*1000+time.tv_usec*0.001;
	return(now);
}
/*void usleep_new(int ml)
{
	int result;
	result=get_now()+ml;
	while (get_now()<result)
		usleep(1000);
}*/
void usleep_new(int ml)
{
	int result;
	struct timeval start;
	gettimeofday(&start,0);
	while(get_time(start)<ml)
		usleep(2000);
}