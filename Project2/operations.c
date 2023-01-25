
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "operations.h"
extern int* arr;
extern int n;


void* min(void* args){
    // int min = INT32_MAX;
    // for (int i = 0; i < n; i++)
    // {
    //     printf("%d %d\n",i,arr[i]);
    //     if(arr[i] < min){
    //         min = arr[i];
    //     }
    // }
    tdata *data = (tdata *)args;
    int* res = malloc(sizeof(int));
    *res = arr[0];
    data->min=arr[0];
    
    return (void*)res;
    
    
}
void* max(void* args){
    // int max = 0;
    // for (size_t i = 0; i < n; i++)
    // {
    //     if(arr[i] > max){
    //         max = arr[i];
    //     }
    // }
    tdata *data = (tdata *)args;

    int* res = malloc(sizeof(int));
    *res = arr[n-1];
    data->max=arr[n-1];
    return (void*)res;
    
    

}

void* range(void* args){
    
    tdata *data = (tdata *)args;
    int i = *(int*)max(args)-*(int*)min(args);
    int* res = malloc(sizeof(int));
    *res = i;
    data->range=i;
    return (void*)res;
}

void* mode(void* args){
    tdata *data = (tdata *)args;
    int cpyarr[n];
    for(size_t i =0;i <n;i++){
        cpyarr[i]=0;
    }
    
    for (size_t i = 0; i < n; i++)
    {
        for (size_t k = 0; k < n; k++)
        {
            if(arr[i] == arr[k]){
                cpyarr[i]++;
            }
        }
        
    }

    int max = cpyarr[0];
    int mode= arr[0];
    for (size_t i = 0; i < n; i++)
    {
        if(cpyarr[i] > max){ // ilkini döndürüyor
            max = cpyarr[i];
            mode = arr[i];
        }

    }
    
    data->mode=mode;
    return NULL;
    
    
}

void* sum(void* args){
    tdata *data = (tdata *)args;
    float sum=0;
    for (size_t i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    float* ret = malloc(sizeof(float));
    *ret=sum;
    data->sum=sum;
   
    return (void*)ret;
}


void* a_mean(void* args){
    //return (float)sum(sargs)/(float)sargs.n;
    tdata *data = (tdata *)args;
    float f = *((float*)sum(args))/(float)n;
    float* res = malloc(sizeof(float));
    *res = f;
    data->mean=f;
    return (void*)res;
}

void* median(void* args){
    
    tdata *data = (tdata *)args;
   
   

    float f;

    if((n)%2 == 0){
        int a = n/2;
        f= ((float)arr[a] + (float)arr[a-1])/2;
    }
    else{
        int a = (n-1)/2;
        f= arr[a];
    }


    float* res = malloc(sizeof(float));
    *res = f;
    data->median = f;
    return (void*)res;
}

void* h_mean(void* args)
{
    tdata *data = (tdata *)args;
    // Declare sum variables and initialize with zero.
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum = sum + (float)1 / (float)arr[i];
    float f = (float)n / sum;
    float* res = malloc(sizeof(float));
    *res = f;
    data->hmean = f;
    return (void*)res;
}

void* stddev(void* args){
    float var = 0;
    float avg = 0;
    int i;
    tdata *data = (tdata *)args;
    /* fetches the average */
    //avg = a_mean(sargs);

    /* adds up all double values of the sample. */
    for (i = 0; i < n; i++)
    {
        var += (arr[i] - avg) * (arr[i] - avg);
    }

    var /= (float)(n - 1);

    float f = (float) sqrt(var);
    float* res = malloc(sizeof(float));
    *res = f;
    data->stddev = f;
    return (void*)res;
}


void* interqrange(void* args){

    tdata *data = (tdata *)args;
    float q1;
    float q3;
    int k=0;
    if(n%4 ==0){
        k=n/4;
        q1 = (arr[k-1]+arr[k]) / (float)2;
        q3 = (arr[3*k-1]+arr[3*k]) / (float)2;
    }
    if(n%4 ==1){
        k = (n-1)/4;
        q1 = (arr[k-1]+arr[k]) / (float)2;
        q3 = (arr[3*k+1]+arr[3*k]) / (float)2;
    }
    if(n%4 ==2){
        k = (n-2)/4;
        q1 = arr[k];
        q3 = arr[3*k];
    }
    if(n%4 ==3){
        k = (n-3)/4;
        q1 = arr[k];
        q3 = arr[3*k+1];
    }

    data->interqrange= q3 - q1;
    return NULL;
}


int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}


