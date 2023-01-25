#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *out_file;

struct customer_data
{
    int sleep_time;
    int vend_m_id;
    char comp_name[10];
    int amount;
    int customer_id;
};


pthread_mutex_t mutexKevin, mutexBob, mutexStuart, mutexOtto, mutexDave;
pthread_mutex_t vend_locks[10];
pthread_mutex_t fileMutex;


int balanceDave = 0;
int balanceKevin = 0;
int balanceBob = 0;
int balanceStuart = 0;
int balanceOtto = 0;

struct customer_data *datas[10];


void *customer(void *cust_data)
{

    struct customer_data data = *(struct customer_data *)cust_data;
    
    pthread_mutex_lock(&vend_locks[data.vend_m_id]);

    usleep(data.sleep_time*1000);
    datas[data.vend_m_id] = cust_data;

    pthread_exit(NULL);
}

void *vending_m(void *args)
{
    int id = *(int *)args;
    
    while (1)
    {

        while (datas[id] != NULL)
        {
            if (strcmp(datas[id]->comp_name, "Kevin") == 0)
            {
                pthread_mutex_lock(&mutexKevin);
                balanceKevin += datas[id]->amount;
                pthread_mutex_unlock(&mutexKevin);
            }
            else if (strcmp(datas[id]->comp_name, "Bob") == 0)
            {
                pthread_mutex_lock(&mutexBob);
                balanceBob += datas[id]->amount;
                pthread_mutex_unlock(&mutexBob);
            }
            else if (strcmp(datas[id]->comp_name, "Stuart") == 0)
            {
                pthread_mutex_lock(&mutexStuart);
                balanceStuart += datas[id]->amount;
                pthread_mutex_unlock(&mutexStuart);
            }
            else if (strcmp(datas[id]->comp_name, "Otto") == 0)
            {
                pthread_mutex_lock(&mutexOtto);
                balanceOtto += datas[id]->amount;
                pthread_mutex_unlock(&mutexOtto);
            }
            else if (strcmp(datas[id]->comp_name, "Dave") == 0)
            {
                pthread_mutex_lock(&mutexDave);
                balanceDave += datas[id]->amount;
                pthread_mutex_unlock(&mutexDave);
            }
            

            pthread_mutex_lock(&fileMutex);
            fprintf(out_file,"Customer%d,%dTL,%s\n",datas[id]->customer_id,datas[id]->amount,datas[id]->comp_name);
            pthread_mutex_unlock(&fileMutex);


            datas[id] = NULL;

            pthread_mutex_unlock(&vend_locks[id]);
        }
    }
    pthread_exit(NULL);
}

int main(int argc,char* argv[])
{

    for (size_t i = 0; i < 10; i++)
    {
        datas[i] = NULL;
    }
    char* inputfilename = argv[1];

    char filename[100];
    strcpy(filename,inputfilename);
    char* seperatedName = strtok(filename,".");
    char outfilename[100];
    sprintf(outfilename,"%s_log.txt",seperatedName);

    FILE *file = fopen(inputfilename, "r");
    out_file = fopen(outfilename, "w");

    char line[200];

    // parse line to int to get the number of customers as integer
    fgets(line, sizeof(line), file);
    int n_customer = atoi(line);

    struct customer_data *customerData[n_customer];
    int index = 0;

    while (fgets(line, sizeof(line), file))
    {
        
        char *token = strtok(line, ",");
        int sleepTime = atoi(token);

        token = strtok(NULL, ",");
        int vmid = atoi(token);

        token = strtok(NULL, ",");
        char *compName = token;

        token = strtok(NULL, ",");
        int amount = atoi(token);

        customerData[index] = (struct customer_data *)malloc(sizeof(struct customer_data));

        customerData[index]->amount = amount;
        customerData[index]->sleep_time = sleepTime;
        customerData[index]->vend_m_id = vmid - 1;
        strcpy(customerData[index]->comp_name, compName);
        customerData[index]->customer_id = index;
        index++;
    }


    for (size_t i = 0; i < 10; i++)
    {
        pthread_mutex_init(&vend_locks[i], NULL);
    }

    pthread_mutex_init(&mutexKevin, NULL);
    pthread_mutex_init(&mutexBob, NULL);
    pthread_mutex_init(&mutexOtto, NULL);
    pthread_mutex_init(&mutexStuart, NULL);
    pthread_mutex_init(&mutexDave, NULL);
    pthread_mutex_init(&fileMutex,NULL);


    pthread_t customerThreads[n_customer];
    pthread_t vendmThreads[10];

    for (int i = 0; i < 10; i++)
    {
        // int in = i;
        int *indx = malloc(sizeof(int));
        *indx = i;
        pthread_create(&vendmThreads[i], NULL, vending_m, (void *)indx);
    }
    sleep(1);
    for (int i = 0; i < n_customer; i++)
    {
        pthread_create(&customerThreads[i], NULL, customer, (void *)customerData[i]);
    }


    for (size_t i = 0; i < n_customer; i++)
    {
        pthread_join(customerThreads[i], NULL);
    }

    fprintf(out_file,"All prepayments are completed\n");
    fprintf(out_file,"Kevin: %dTL\nBob: %dTL\nStuart: %dTL\nOtto: %dTL\nDave: %dTL\n",balanceKevin,balanceBob,balanceStuart,balanceOtto,balanceDave);


    return 0;
}
