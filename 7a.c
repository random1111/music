#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

int main()
{
        int fd[2];
        int i = 0;
        char txt;
        int fd1[2];
        pipe(fd);
        pipe(fd1);
        char buffer[1000]={'\0'};
        char msg[] = "file.txt";
        pid_t pid;
        pid = fork();
                if( pid == 0 )
                {
                        close(fd[0]);
                        write(fd[1],msg,strlen(msg));
                        close(fd[1]);
                        close(fd1[1]);
                        read(fd1[0],buffer,sizeof(buffer));
                        close(fd1[0]);
                        printf("%s",buffer);
                }
                else
                {
                        i = 0;
                        close(fd[1]);
                        read(fd[0],msg,sizeof(msg));
                        close(fd[0]);                
                        printf("%s\n",msg);
                        FILE *fp;
                        fp = fopen(msg,"r");
                        while(!feof(fp))
                        {
                                txt = fgetc(fp);
                                buffer[i] = txt;
                                i++;
                        }        
                        buffer[i]='\0';
                        fclose(fp); 
                        close(fd1[0]);     
                        write(fd1[1],buffer,i);
                        close(fd1[1]);
                }
         return 0;
}
