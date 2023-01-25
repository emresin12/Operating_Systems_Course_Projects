

struct statargs
{
    int n;
    int* arr;
};

typedef struct tdata
{
    int min;
    int max;
    int range;
    int mode;
    float median;
    int sum;
    float mean;
    float hmean; 
    float stddev;
    float interqrange;
} tdata;


void* min(void* args);
void* max(void* args);
void* range(void* args);
void* mode(void* args);
void* median(void* args);
void* sum(void* args);
void* a_mean(void* args);
void* h_mean(void* args);
void* stddev(void* args);
void* interqrange(void* args);
int compare (const void * a, const void * b);



