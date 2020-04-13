#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
pthread_mutex_t l=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t l1=PTHREAD_MUTEX_INITIALIZER;
int counter=1;
void *read1()
{
	pthread_mutex_lock(&l1);
	int a;
	a=counter;
	printf("In First Reader\n");
	//sleep(2);
	printf("Value of Shared Variable after first read is %d\n",counter);
	pthread_mutex_unlock(&l1);
}
void *write1()
{
	pthread_mutex_lock(&l);
	int c;
	c=counter;
	sleep(2);
	printf("In Writer\n");
	c=c+1;
	counter=c;
	printf("Value of Shared Variable after write thread is %d\n",counter);
	pthread_mutex_unlock(&l);
}
void *read2()
{
	int a;
	a=counter;
	printf("In Second Reader\n");
	sleep(1);
	printf("Value of Shared Variable is %d\n",a);
}
int main()
{
	pthread_t t1,t2,t3;
	int i;
	for(i=1;i<=2;i++)
	{
		printf("<<<<<| CASE %d |>>>>>\n",i);
	    pthread_create(&t3,NULL,write1,NULL);
	    pthread_create(&t1,NULL,read1,NULL);
	    pthread_create(&t2,NULL,read2,NULL);
	    pthread_join(t3,NULL);
	    pthread_join(t1,NULL);
	    pthread_join(t2,NULL);
	    printf("\n");
	    printf("The value of counter: %d\n",counter);
	    printf("\n\n");
	}
}
