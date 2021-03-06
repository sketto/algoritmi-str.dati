#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include "funzioni.h"

#define RAND_SEED 200

void insertionSort(int *array, int length)
{
    int j;
    int i;
    int key;
    // printf("\narray[j]: %d\n", array[j]);

    for (j = 1; j < length; j++)
    {
        key = array[j];
        i = j - 1;

        while (i >= 0 && array[i] > key)
        {
            array[i + 1] = array[i];
            i = i - 1;
        }

        array[i + 1] = key;
    }
}

/**
 * funzione che genera un array di lunghezza "lenght" di numeri casuali
 **/
int *generateRandomArray(int length)
{
    int *vet = malloc(length * sizeof(int)); //per evitare "warning: function returns address of local variable" è utile allocare la memoria dinamicamente
    int fre[RAND_SEED] = {0};
    int i;

    srand(time(NULL));

    for (i = 0; i < length; i++)
    {
        vet[i] = (rand() % RAND_SEED);
    }

    for (i = 0; i < length; i++)
    {
        fre[vet[i]] = fre[vet[i]] + 1;
    }
    return vet;
}

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

        insertionSort(array, length);

        t_end = clock();
        t_elapsed = t_end - t_start;

        t_tot = t_tot + t_elapsed;
    }

    return t_tot / maxInstances;
}

void experiment(int minLength, int maxLength)
{

    int maxInstances = 5;
    int step = 5;
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
    //experiment(5, 2000);
    int length = 10;
    int *array = generateRandomArray(length);
    int i;

    printf("prima\n");

    for (i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }

    insertionSort(array, length);

    printf("\ndopo\n");

    for (i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }

    return 0;
}