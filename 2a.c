#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
   
   void sort_asc(int a[],int n)
 { int i,j,temp;
   for(i=0;i<n-1;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
        if(a[j]>a[j+1])
        {
          temp=a[j];
          a[j]=a[j+1];
	  a[j+1]=temp;	
        }
      }       
   }     
  

  
   printf("\nSorted Array");
	for(i=0;i<n;i++)
	{ 
		printf("\n%d\n", a[i]);
	}

 }

   void sort_des(int a[],int n)
 { 
	int i,j,temp;
   
   for(i=0;i<n-1;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
        if(a[j]<a[j+1])
        {
          temp=a[j];
          a[j]=a[j+1];
	  a[j+1]=temp;	
        }
      }       
   }     
 

  
           printf("\nSorted Array:\n");
	     for(i=0;i<n;i++) 
            {
		printf("%d\n", a[i]);
            }

   }
 int main()
 {  int a[30],n,i; 
   printf("enter the size of array\n");
   scanf("%d",&n);
   printf("enter the %d elements:\n",n);
   for(i=0;i<n;i++)
   {
     scanf("%d",&a[i]);
   }  
   pid_t pid;
   pid=fork();

      if(pid==0)
     {
                
		printf("Child process");
		sort_asc(a,n);
		
      

     }
      else
     {          printf("Parent Process");
		sort_des(a,n);
	
 
     }
       return 0;

 }

