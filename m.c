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
int main()
{
	struct timeval s;

	gettimeofday(&s,0);
	while (1)
	{
		usleep(200*1000);
		printf("%d\n",get_time(s));
	}
}