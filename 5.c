#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t x;
pthread_mutex_t wsem;
int readcount=0;
FILE *fp;
char str[20];
char txt;

void *writer(void *thread)
{
	int t=*(int *)thread;
	pthread_mutex_lock(&wsem);
	
	printf("\nEnter the name of file to open\n");
	scanf("%s",str);
	
	fp=fopen(str,"a");
	
	printf("Enter the character to be inserted in file(to exit entering,press 'q'):\n");
	
	do
	{
		scanf("%c",&txt);
		
		if(txt!='q')
		{
			fputc(txt,fp);
		}
	}while(txt!='q');
	fclose(fp);
	sleep(1);
	
	pthread_mutex_unlock(&wsem);
}

void *reader(void *thread)
{
	int t=*(int *)thread;
	pthread_mutex_lock(&x);
	readcount++;
	if(readcount==1)
		pthread_mutex_lock(&wsem);
	pthread_mutex_unlock(&x);
	
	printf("Enter the file name to open\n");
	scanf("%s",str);
	
	fp=fopen(str,"r");
	while(!feof(fp))
	{
		txt=fgetc(fp);
		
		printf("%c",txt);
		//printf("\n");
	}
	fclose(fp);
	sleep(1);
	
	pthread_mutex_lock(&x);
	readcount--;
	if(readcount==0)
		pthread_mutex_unlock(&wsem);
	pthread_mutex_unlock(&x);
	
	
}
int main()
{
	pthread_t tid[10];
	int i,tnum[10];
	pthread_mutex_init(&x,NULL);
	pthread_mutex_init(&wsem,NULL);
	
	for(i=0;i<10;i++)
	{
		tnum[i]=i;
		pthread_create(&tid[i],NULL,writer,&tnum[i]);
		i++;
		tnum[i]=i;
		pthread_create(&tid[i],NULL,reader,&tnum[i]);
	}
	for(i=0;i<10;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_mutex_destroy(&x);
	pthread_mutex_destroy(&wsem);
	return 0;
}
