#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#define SHMSZ 27

main()
{
	char c;
	int shmid;
	key_t key;
	char *shm = NULL, *s = NULL;
	
	key=5678;
	
	if((shmid=shmget(key,SHMSZ,IPC_CREAT | 0666))<0)
	{
			perror("shmget");
			exit(1);
	}
	//shm_ptr = (int *) shmat(shmid, NULL, 0);  /* attach */
	if((shm=(char *)shmat(shmid,NULL,0))==-1)
	{
		perror("shmat");
		exit(1);
	}
	
	s=shm;
	printf("\nEnter the message to send to the client");
	gets(s);
	
	while(*shm!='*')
		sleep(1);
	exit(0);
}    
------------------------sharec.c--------------------
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>

#define SHMSZ 27

main()
{
	int shmid;
	key_t key;
	char *shm = NULL, *s = NULL;
	
	key=5678;
	
	if((shmid=shmget(key,SHMSZ,0666))<0)
	{
		perror("shmget");
		exit(1);
	}
	
	if((shm=(char *)shmat(shmid,NULL,0))==-1)
	{
		perror("shmat");
		exit(1);
	}
	for(s=shm;*s!='\0';s++)//doubt
		putchar(*s);
	putchar('\n');
	
	*shm='*';
	exit(0);
}
	
