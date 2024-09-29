#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int *get_random_array(int len)
{
    int *arr = (int *)malloc(sizeof(int) * len);
    time_t curtime;
    srand(time(&curtime));

    for (int i = 0; i < len; i++)
    {
        arr[i] = rand() % 100;
    }
    return arr;
}

int arrsum(int a[],int len){
    int s = 0;
    for (int i = 0; i < len; i++)
    {
        s+=a[i];
    }
    return s;
}