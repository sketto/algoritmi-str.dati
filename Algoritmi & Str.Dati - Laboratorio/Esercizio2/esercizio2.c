#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include "funzioni.h"


clock_t singleExperiment(int length, int maxInstances)
{

    int *array;
    int i, j;
    clock_t t_tot = 0;
    

    for (i = 0; i < maxInstances; i++)
    {

        clock_t t_start, t_end, t_elapsed;

        array = generateRandomArray(length);

        t_start = clock();

        array = insertionSort(array, length);

        t_end = clock();
        t_elapsed = t_end - t_start;
       
        t_tot = t_tot + t_elapsed;
    }
    
    return t_tot / maxInstances;
}

void experiment(int minLength, int maxLength)
{

    int maxInstances = 50;
    int step = 1000;
    clock_t time;
    int length;

    for (length = minLength; length <= maxLength; length += step)
    {
        time = singleExperiment(length, maxInstances);
        printf("%ld; %d\n", (long int)(time), length);
    }
}

int main()
{
    //experiment(1000, 50000);
    int array[10] = {5, 9, 4, 0, 3, 12, 56, 90, 11, 34};
    mergeSort(array, 0, 9);


    return 0;
}