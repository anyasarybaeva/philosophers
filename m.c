#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/time.h>
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
	printf("%ld\n",time.tv_sec);
	now=time.tv_sec*1000+time.tv_usec*0.001;
	printf("%d\n",now);
	return(now);
}
void usleep_new(int ml)
{
	int result;
	struct timeval start;
	gettimeofday(&start,0);
	while(get_time(start)<ml)
		usleep(100);
}
int main()
{
	struct timeval s;

	gettimeofday(&s,0);
	while (1)
	{
		usleep_new(200);
		printf("%d\n",get_time(s));
	}
}