#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>

#define MAXRESOURCES 5
#define MAXTHREADS 6

int available_resources = MAXRESOURCES;
pthread_mutex_t mtx;
int sz = MAXTHREADS;
int cnt_threads[MAXTHREADS] = {4,6,3,5,9,7};

int decrease_count(int count)
{
    int error = pthread_mutex_lock(&mtx);     
    if(!error && count<=available_resources)
    {                                                                        
        available_resources -= count;                           
        printf("Got %d resources, %d remaining\n", count, available_resources);
    }
    return pthread_mutex_unlock(&mtx);                   
}

int increase_count(int count)
{
    int error = pthread_mutex_lock(&mtx);            
    if(!error && available_resources+count<=MAXRESOURCES)
    {
         available_resources += count;
         printf("Released %d resources, %d remaining\n", count, available_resources);
    }
    return pthread_mutex_unlock(&mtx);               
}
void* my_thread(void* x)         
{
    int count = *((int*)x); 
    decrease_count(count); 
    increase_count(count);
    return NULL;
}
int main(){
    if (pthread_mutex_init(&mtx, NULL))  
    {
        perror(NULL);
        return errno ;
    }
    printf("MAX_RESOURCES=%d\n", MAXRESOURCES);
    pthread_t* thr = malloc(sz * sizeof(pthread_t));
    for(int i=0;i<sz;++i)
        pthread_create(&thr[i], NULL, my_thread, &cnt_threads[i]);    
    for(int i=0;i<sz;++i)
        pthread_join(thr[i], NULL);        
    pthread_mutex_destroy(&mtx);          
    return 0;
}