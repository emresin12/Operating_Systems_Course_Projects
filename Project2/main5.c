#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "operations.h"



void* runner1(void* args);
void* runner2(void* args);
void* runner3(void* args);
void* runner4(void* args);
void* runner5(void* args);



int* arr;

int n;
int main(int argc, char *argv[]){

    int N = atoi(argv[1]);
    arr = (int*)malloc(sizeof(int)*N);
    n= N;
    time_t t1;
    srand((unsigned)time(&t1)); 

    //printf("%d",N);
    for (size_t i = 0; i < N; i++)
    {
        
        arr[i] = (rand()%9000)+1000;
        //printf("%d ",arr[i]);
    }
    printf("\n");

    qsort(arr,N,sizeof(int),compare);

    tdata t_data;
  
    pthread_t thread_id[5];


    struct timespec start, finish;
    double time;
    clock_gettime(CLOCK_REALTIME, &start);

    pthread_create(&thread_id[0], NULL, runner1,(void*) &t_data);
    pthread_create(&thread_id[1], NULL, runner2,(void*) &t_data);
    pthread_create(&thread_id[2], NULL, runner3,(void*) &t_data);
    pthread_create(&thread_id[3], NULL, runner4,(void*) &t_data);
    pthread_create(&thread_id[4], NULL, runner5,(void*) &t_data);
    
    pthread_join(thread_id[0], NULL);
    pthread_join(thread_id[1], NULL);
    pthread_join(thread_id[2], NULL);
    pthread_join(thread_id[3], NULL);
    pthread_join(thread_id[4], NULL);

    clock_gettime(CLOCK_REALTIME, &finish);
    
    time = (finish.tv_sec-start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    FILE *fp;    
    fp = fopen("output2.txt","w");

    fprintf(fp,"%d\n",t_data.min);
    fprintf(fp,"%d\n",t_data.max);
    fprintf(fp,"%d\n",t_data.range);
    fprintf(fp,"%d\n",t_data.mode);
    fprintf(fp,"%f\n",t_data.median);
    fprintf(fp,"%d\n",t_data.sum);
    fprintf(fp,"%f\n",t_data.mean);
    fprintf(fp,"%f\n",t_data.hmean);
    fprintf(fp,"%f\n",t_data.stddev);
    fprintf(fp,"%f\n",t_data.interqrange);
    fprintf(fp,"%lf\n", time);
    return 0;
}

void* runner1(void* args){
    min(args);
    max(args);
    return NULL;

}
void* runner2(void* args){
    range(args);
    mode(args);
    return NULL;
}
void* runner3(void* args){
    median(args);
    sum(args);
    return NULL;

}
void* runner4(void* args){
    a_mean(args);
    h_mean(args);
    return NULL;
}
void* runner5(void* args){
   stddev(args);
   interqrange(args);
   return NULL;
}