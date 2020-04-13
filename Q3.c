#include <semaphore.h>
#include <unistd.h>
#include<stdio.h>
#include<pthread.h>

sem_t sem1;
int shared=10;

void *thread1()
{
	int x;
	sem_wait(&sem1);
	x=shared;
	x++;
	sleep(2);
	shared=x;
	printf("Thread 1, shared = %d\n", shared);
	sem_post(&sem1);
}

void *thread2()
{
	int x;
	sem_wait(&sem1);
	x=shared;
	x++;
	sleep(2);
	shared=x;
	printf("Thread 2, shared = %d\n", shared);	
	sem_post(&sem1);
}

void *thread3()
{
	int x;
	sem_wait(&sem1);
	x=shared;
	x++;
	sleep(2);
	shared=x;
	printf("Thread 3, shared = %d\n", shared);
	sem_post(&sem1);
}

int main()
{
  pthread_t t1, t2, t3;
  sem_init(&sem1, 0, 2);

  printf("Initially, shared = %d\n", shared);
  
  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);
  pthread_create(&t3, NULL, thread3, NULL);
  
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  
  return 0;
}
