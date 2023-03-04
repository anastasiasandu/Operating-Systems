#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/errno.h>

int main()
{
    pid_t pid=fork();  
    if(pid<0) 
    {
        perror("eroare\n"); 
        return errno;
    }
    else if(pid==0)  
    {
        char *argv[]={"pwd", NULL};  
        execve("/usr/bin/pwd", argv, NULL); 
        perror(NULL);  
    }
    else if(pid>0)
    {
        printf("My PID=%d, Child PID=%d.\n", getppid(), getpid());   
        wait(NULL); 
        printf("Child %d finished.\n",  getpid());
    }

    return 0;
}