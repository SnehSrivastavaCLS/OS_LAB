#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
int counter=5;
pthread_mutex_t l=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t l1=PTHREAD_MUTEX_INITIALIZER;
void *read1()
{
pthread_mutex_lock(&l1);
int a;
a=counter;
printf("i am in first reader\n");
sleep(2);
printf("the value of shared variable is=%d\n",counter);
pthread_mutex_unlock(&l1);
}
void *write1()
{
pthread_mutex_lock(&l);
int c;
c=counter;
printf("i am in writer ");
sleep(2);
c=c+1;
counter=c;
printf("the value of shared variable is=%d\n",counter);
pthread_mutex_unlock(&l);
}
void *read2()
{
int a;
a=counter;
printf("i am in second reader\n");
printf("the value of shared variable is %d\n",a);
}
int main()
{
pthread_t t1,t2,t3;

pthread_create(&t3,NULL,write1,NULL);
pthread_create(&t1,NULL,read1,NULL);
pthread_create(&t2,NULL,read2,NULL);
pthread_join(t1,NULL);
pthread_join(t3,NULL);
pthread_join(t2,NULL);
printf("the value of counter =%d\n",counter);
}
