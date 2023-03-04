#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define rows 3
#define cols 3

int matrix1[rows][cols] = {
        {213,1234,425},
        {7438,3,4},
        {10,252,326}
};
int matrix2[rows][cols] = {
        {84,56,45},
        {23,345,56},
        {89,789,67}
};
int result_matrix[rows][cols];
struct pos
{
    int i, j;
};
void* compute(void* position)  
{
    struct pos * index = position;
    int i = index->i;
    int j = index->j;
    result_matrix[j][i] = 0;
    for(int k=0;k<cols;++k)
        result_matrix[j][i] = matrix1[j][k]*matrix2[k][i] + matrix1[j][k+1]*matrix2[k+1][i]+matrix1[j][k+2]*matrix2[k+1][i];
    return NULL;
}
int main(){
    pthread_t threads[rows*cols];    
    int thread_id = 0;
    for(int i=0;i<rows;++i)
        for(int j=0;j<cols;++j){
            struct pos* index = calloc(1, sizeof(struct pos));
            index->i = i;
            index->j = j;
            if(pthread_create(&threads[thread_id++], NULL, compute, index))  
            {
                perror(NULL);
                return errno;
            }
        } 
    thread_id = 0; 
    void *result;
	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
        {
            if(pthread_join(threads[thread_id++], &result))  
            {
				perror(NULL);
				return errno;
			} 
        }
    printf("\n\nREZULTAT:\n");
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++) 
            printf("%d ", result_matrix[i][j]);
        printf("\n");
    } 
    return 0;
}