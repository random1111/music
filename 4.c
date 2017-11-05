#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>

int buffer[5];
int buff_index=0;
sem_t full_sem;
sem_t empty_sem;
pthread_mutex_t buffer_mutex;

void *producer(void *thread)
{
	int r=rand()%100;
	int t=*(int *)thread;
	sem_wait(&empty_sem);
	pthread_mutex_lock(&buffer_mutex);
	buffer[buff_index++]=r;
	pthread_mutex_unlock(&buffer_mutex);
	sem_post(&full_sem);
	
	printf("\nProducer %d has placed element %d into the buffer",t,r);
	pthread_exit(NULL);
}
void *consumer(void *thread)
{
	int t=*(int *)thread;
	sem_wait(&full_sem);
	pthread_mutex_lock(&buffer_mutex);
	buffer[--buff_index];
	pthread_mutex_unlock(&buffer_mutex);
	sem_post(&empty_sem);
	printf("\nConsumer %d has removed element from the buffer",t);
	pthread_exit(NULL);
}	
main()
{
	pthread_t tid[10];
	int a[10],i;
	pthread_mutex_init(&buffer_mutex,NULL);
	sem_init(&full_sem,0,0);
	sem_init(&empty_sem,0,5);
	for(i=0;i<10;i++)
	{
		a[i]=i;
		pthread_create(&tid[i],NULL,producer,&a[i]);
		i++;
		a[i]=i;
		pthread_create(&tid[i],NULL,consumer,&a[i]);
	}
	for(i=0;i<10;i++)
	{
		pthread_join(tid[i],NULL);
	}
	sem_destroy(&full_sem);
	sem_destroy(&empty_sem);
	pthread_mutex_destroy(&buffer_mutex);
}

