#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <sys/mman.h>

int main(int argc, char *argv[])
{
    int i;
    printf(" %d\n", getpid());
    //parintele creeaza ob de mem part
    char *shm_name="lab5";  
    int shm_fd;
    shm_fd=shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);//creez ob de mem partajata lab5, r si w doar utilizatorului
    if(shm_fd<0)
    {
        return errno;
    }
    size_t page_size=getpagesize(); 
    size_t shm_size=page_size*argc;   //impart memoria in mod egal pentru fiecare copil 
    if(ftruncate(shm_fd, shm_size)==-1)  
	{
        shm_unlink(shm_name); 
		return errno;
	}
	char *shm_ptr; 
	for(i=1; i<argc; i++)
    {
        shm_ptr=mmap(0, page_size, PROT_WRITE, MAP_SHARED, shm_fd, (i-1)*page_size); //incarc memoria partajata in spatiul procesului
        if(shm_ptr==MAP_FAILED)
		{
            shm_unlink(shm_name);    //sterg obiectul creat
			return errno;
		}
		pid_t pid=fork(); 
        if(pid<0) {return errno;}
        else if(pid==0) //copil
        {
            int x=atoi(argv[i]);
            shm_ptr+=sprintf(shm_ptr, "%d: %d ", x, x); //formatez outputul, incarcam in zona de memorie nr din ipoteza collatz
            while(x!=1)
            {
                if(x%2==0) x/=2;
                else x=3*x+1;
                shm_ptr+=sprintf(shm_ptr, "%d ", x);
            }
            printf("  %d   %d\n",  getppid(), getpid());
            return 1;
        }
        munmap(shm_ptr,page_size);  //eliberez zona de memorie
    }
    for(i=1; i<argc; i++) 
    {
        wait(NULL);   //parintele asteapta ca fiecare copil sa isi termine executia
    }
    for(i=1; i<argc; i++) //afisez procesele-copil (fiecare cu zona de memorie)
    {
        shm_ptr=mmap(0, page_size, PROT_READ, MAP_SHARED, shm_fd, (i-1)*page_size);
		printf("%s\n", shm_ptr);
        munmap(shm_ptr,page_size);
	}
    shm_unlink(shm_name);  
	printf(" %d  %d\n", getppid(), getpid());
    return 0;
}