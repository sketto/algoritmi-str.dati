#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define RAND_SEED 200
#define K 100

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

void merge(int *array, int p, int q, int r)
{
    int i, j, k;
    i = p;
    j = q + 1;
    k = 0;
    int tmp[r - p + 1];

    while (i <= q && j <= r)
    {
        if (array[i] < array[j])
        {
            tmp[k] = array[i];
            i++;
        }
        else
        {
            tmp[k] = array[j];
            j++;
        }
        k++;
    }
    while (i <= q)
    {
        tmp[k] = array[i];
        i++;
        k++;
    }
    while (j <= r)
    {
        tmp[k] = array[j];
        j++;
        k++;
    }
    for (k = p; k <= r; k++)
    {
        array[k] = tmp[k - p];
    }
}

void mergeSort(int *array, int p, int r)
{
    if (p < r)
    {

        int q;
        q = (p + r) / 2;
        mergeSort(array, p, q);
        mergeSort(array, q + 1, r);
        merge(array, p, q, r);
    }
}

void hybridSort(int *array, int p, int r)
{
    int length = r - p + 1;

    if (length > K)
    {
        int q = (p + r) / 2;
        hybridSort(array, p, q);
        hybridSort(array, q + 1, r);
        merge(array, p, q, r);
    }
    else
    {
        //printf("\nlength: %d\n", length);

        insertionSort(array, length);
    }
}