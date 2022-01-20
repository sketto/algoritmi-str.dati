#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include "funzioni.h"

// clock_t singleExperiment(int length, int maxInstances)
// {

//     int *array;
//     int i, j;
//     clock_t t_tot = 0;

//     for (i = 0; i < maxInstances; i++)
//     {

//         clock_t t_start, t_end, t_elapsed;

//         array = generateRandomArray(length);

//         t_start = clock();

//         mergeSort(array, 0, length - 1);

//         t_end = clock();
//         t_elapsed = t_end - t_start;

//         t_tot = t_tot + t_elapsed;
//     }

//     return t_tot / maxInstances;
// }

// void experiment(int minLength, int maxLength)
// {

//     int maxInstances = 5;
//     int step = 5;
//     clock_t time;
//     int length;

//     for (length = minLength; length <= maxLength; length += step)
//     {
//         time = singleExperiment(length, maxInstances);
//         printf("%ld; %d\n", (long int)(time), length);
//     }
// }

clock_t singleExperiment(int length, int maxInstances, int alg)
{

    int *array;
    int i, j;
    clock_t t_tot = 0;

    for (i = 0; i < maxInstances; i++)
    {

        clock_t t_start, t_end, t_elapsed;

        array = generateRandomArray(length);

        //int index;
        // printf("random array:\n");
        // for (index = 0; index < length; index++)
        // {
        //     printf(" %d ", array[index]);
        // }
        // printf("\n");

        if (alg == 1) //IS
        {
            t_start = clock();
            insertionSort(array, length);

            // printf("after IS:\n");
            // for (index = 0; index < length; index++)
            // {
            //     printf(" %d ", array[index]);
            // }
            // printf("\n");

            t_end = clock();
        }
        else if (alg == 2) //MG
        {
            t_start = clock();
            mergeSort(array, 0, length - 1);

            // printf("after MS:\n");
            // for (index = 0; index < length; index++)
            // {
            //     printf(" %d ", array[index]);
            // }
            // printf("\n");

            t_end = clock();
        }
        else if (alg == 3) //HS
        {
            t_start = clock();
            hybridSort(array, 0, length - 1);

            // printf("after HS:\n");
            // for (index = 0; index < length; index++)
            // {
            //     printf(" %d ", array[index]);
            // }
            // printf("\n");

            t_end = clock();
        }

        t_elapsed = t_end - t_start;
        t_tot = t_tot + t_elapsed;
    }

    clock_t t_final = t_tot / maxInstances; //prendere tempo come double

    return t_final;
}

void experiment(int minLength, int maxLength)
{

    int maxInstances = 5;
    int step = 5;
    clock_t timeIS, timeMS, timeHS;
    int length;

    for (length = minLength; length <= maxLength; length += step)
    {
        timeIS = singleExperiment(length, maxInstances, 1);
        timeMS = singleExperiment(length, maxInstances, 2);
        timeHS = singleExperiment(length, maxInstances, 3);

        //IS; MS; HS; DIM
        printf(" %ld; %ld; %ld; %d\n", (long int)(timeIS), (long int)(timeMS), (long int)(timeHS), length);
    }
}

int main()
{
    //experiment(1000, 50000);
    // int array[10] = {5, 9, 4, 0, 3, 12, 56, 90, 11, 34};
    //mergeSort(array, 0, 9);
    experiment(5, 1500);

    return 0;
}

//aggiungere adaptedInsertionSort