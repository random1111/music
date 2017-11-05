#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
int main()
{
     int fd,fd1,i = 0;
     FILE *fp;
     int lines=1,words=1,characters=0;
     char msg[30];
     mkfifo("myfifo",0666);
     fd = open("myfifo",O_RDONLY);
     read(fd,msg,sizeof(msg));
     int no = strlen(msg)+1;
     while(i<no)
     {
        if(isalpha(msg[i]))
        {
                characters++;
        }
        else if(msg[i] == ' ')
        {
                words++;
        }
        else if(msg[i] == '\n')
        {
                lines++;
        }
        else
        {
        }
        i++;
     }  
     fp = fopen("file1","w");
     fwrite(&characters,sizeof(characters),1,fp);
     fwrite(&words,sizeof(words),1,fp);
     fwrite(&lines,sizeof(lines),1,fp);
     fclose(fp);
     int arr[3] = {characters,words,lines};
     mkfifo("myfifo1",0666);
     fd1 = open("myfifo1",O_WRONLY);
     write(fd1,arr,sizeof(arr));
     close(fd1);
     return 0;
}
-----------------------------------------fifow-----------------
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
     int fd,fd1;
     int i = 0;
     char str[30];
     int arr[3];
     char txt;
     mkfifo("myfifo",0666);
     fd = open("myfifo",O_WRONLY);
     txt = getchar();
     while(txt!='Q')
     {
        str[i] = txt;
        txt = getchar();
        i++;     
     }
     write(fd,str,sizeof(str));
     close(fd);
     mkfifo("myfifo1",0666);
     fd1 = open("myfifo1",O_RDONLY);
     read(fd1,arr,sizeof(arr));
     printf("No of characters are %d\n",arr[0]); 
     printf("No of words are %d\n",arr[1]); 
     printf("No of lines are %d\n",arr[2]); 
}
