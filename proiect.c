#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

#define MAXDOCTORS 6
 
struct doctor
{
    int i;           
    int id;          
    int start;       
    int end;         
};

struct doctor doctors[MAXDOCTORS] = {
                            {1,100,8,16},
                            {2,101,8,16},
                            {3,102,8,16},
                            {4,103,8,16},
                            {5,104,8,16},
                            {6,105,8,16},
                            };
pthread_mutex_t mutexes[MAXDOCTORS];
 
int consult(int time, int interval)
{ 

    for(int i=0; i<MAXDOCTORS; i++)
    {
        
        if ((doctors[i].end - doctors[i].start) >= time && interval >= doctors[i].start)
        {
            int error = pthread_mutex_lock(&mutexes[i]);            
            if(!error)
            {  
                printf("Id-ul doctorului este %d. ", doctors[i].id);
                printf("Timpul consultului este de %d de ore. ", time);
                printf("Timpul de asteptare este de 0 de ore.");
                printf("\n");
                doctors[i].start = doctors[i].start + time;
            }   
            return pthread_mutex_unlock(&mutexes[i]);               
        }
        if ((doctors[i].end - doctors[i].start) >= time && interval < doctors[i].start)
        {
            int error = pthread_mutex_lock(&mutexes[i]);            
            if(!error)
            {  
                printf("Id-ul doctorului este %d. ", doctors[i].id);
                printf("Timpul consultului este de %d de ore. ", time);
                printf("Timpul de asteptare este de %d de ore.", doctors[i].start - interval);
                printf("\n");
                doctors[i].start = doctors[i].start + time;
            }   
            return pthread_mutex_unlock(&mutexes[i]);                
        }
    }
}

void* my_thread(void* x )         
{
    int limit = *(int*)x;   
    int time = (rand() % limit) + 1;                         
    int interval = (rand() %(16 - 8 + 1)) + 8;               
    printf("%d ", interval);
    consult(time, interval);
    return NULL;
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < MAXDOCTORS; i++) 
        if (pthread_mutex_init(&mutexes[i], NULL))  
        {
            perror(NULL);
            return errno ;
        }
    int limit_threads[argc];                                         
    for(int i=2; i<argc; i++)
    {
        int x=atoi(argv[i]);
        limit_threads[i-1]=x;            
    } 

    pthread_t* thr = malloc((argc-1) * sizeof(pthread_t));
    for(int i=1;i<argc-1;++i)
        pthread_create(&thr[i], NULL, my_thread, &limit_threads[i]);    
    
    for(int i=1;i<argc-1;++i)
        pthread_join(thr[i], NULL);         


    for (int i = 0; i < MAXDOCTORS; i++) 
        pthread_mutex_destroy(&mutexes[i]);          
    return 0;
}
