#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "operations.h"


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
  
    pthread_t thread_id[10];
    void* (* func[10])();
    func[0] = min;
    func[1] = max;
    func[2] = range;
    func[3] = mode;
    func[4] = median;
    func[5] = sum;
    func[6] = a_mean;
    func[7] = h_mean;
    func[8] = stddev;
    func[9] = interqrange;

    //interqrange


    struct timespec start, finish;
    double time;
    clock_gettime(CLOCK_REALTIME, &start);

    for (size_t i = 0; i < 10; i++)
    {
        func[i]((void*)&t_data);
    }
    
    clock_gettime(CLOCK_REALTIME, &finish);
    
    time = (finish.tv_sec-start.tv_sec) + (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    
    
    FILE *fp;    
    fp = fopen("output1.txt","w");

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