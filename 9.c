#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<stdlib.h>
# define mbuff 1024
char fname[20];
typedef struct record
{
	char name[20];
	int roll,marks;
}record;
int check(int no)
{
	record r;
	int fd;
	fd=open(fname,O_RDONLY);
	while(read(fd,&r,sizeof(r))>0)
	{
		if(no==r.roll)
		{
			close(fd);
			return 1;
		}
	}
	close(fd);
	return 0;
}
void insert()
{
	record r;
	int no,i;
	int fd=open(fname,O_APPEND|O_WRONLY);
	
	printf("Enter the roll of student\n");
	scanf("%d",&no);
	if(check(no))
	{
		printf("Roll no already present!\n");
	}
	else
	{
		r.roll=no;
		printf("Enter the name of student\n");
		scanf("%s",r.name);
		printf("Enter marks(out of 100)\n");
		scanf("%d",&r.marks);
		write(fd,(void *)&r,sizeof(r));
	}
	close(fd);
}
void display()
{
	record o;
	int fd1,i;
	fd1=open(fname,O_RDONLY);
	printf("Roll\tName\tMarks\n");
	while(read(fd1,&o,sizeof(o))>0)
	{
		printf("%d\t%s\t%d\n",o.roll,o.name,o.marks);
	}
	close(fd1);
}
void modify()
{
	record e;
	int fd,no;
	fd=open(fname,O_RDWR);
	printf("Enter the roll u want to Modify\n");
	scanf("%d",&no);
	while(read(fd,&e,sizeof(e))>0)
	{
		
		if(no==e.roll)
		{
			//printf("%d",no);
			lseek(fd,0-sizeof(e),SEEK_CUR);
			printf("Enter the new name of student\n");
			scanf("%s",e.name);
			printf("Enter the new marks(out of 100)\n");
			scanf("%d",&e.marks);
			write(fd,(void *)&e,sizeof(e));
			break;
		}
	}
	close(fd);
	
}
void del()
{
	record r;
	int no,fd,temp;
	temp=open("newf",O_APPEND|O_WRONLY,0666);
	printf("Enter the roll u want to Delete\n");
	scanf("%d",&no);
	fd=open(fname,O_RDONLY);
	while(read(fd,&r,sizeof(r))>0)
	{
		
		if(no==r.roll)
		{
			printf("Record Deleted\n");
		}
		else
		{
		 	write(temp,(void *)&r,sizeof(r));
		}
	}
	close(fd);
	close(temp);
	remove(fname);
	rename("newf",fname);
}
main()
{
	record r;
	int ch,j,no,fd,i,ffd,temp;
	printf("Enter the name of the file:\n");
	scanf("%s",fname);
	temp=open("newf",O_CREAT|O_APPEND,0666);
	ffd=open(fname,O_CREAT|O_APPEND,0666);
	do
	{
		printf("\nEnter your choice\n");
		printf("1.Create Record\n2.Display\n3.Search\n4.Modify\n5.Delete\n6.Exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:	
				if(ffd<0)
					perror("open");
				else
					insert();
				break;
			case 2:
				display();
				break;
			
			case 3:
				printf("Enter the roll u want to search:\n");
				scanf("%d",&no);
				fd=open(fname,O_RDONLY);
				while(read(fd,&r,sizeof(r))>0)
				{
					if(no==r.roll)
					{
						printf("%s\t%d\t%d\n",r.name,r.roll,r.marks);
						break;
					}
					
				}
				close(fd);
				break;
			case 4:
				modify();
				break;
			case 5:
				del();
				break;
			case 6:
				exit(0);
			
				
					
			}
		}while(ch<7);
}
