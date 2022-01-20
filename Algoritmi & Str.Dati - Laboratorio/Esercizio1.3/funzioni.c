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

void swapValue(int *array, int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

int partition(int *array, int p, int r)
{
    int x, i, j;

    x = array[r];
    i = p - 1;

    for (j = p; j < r; j++)
    {
        if (array[j] <= x)
        {
            i = i + 1;
            swapValue(array, i, j);
        }
    }
    swapValue(array, i + 1, r);

    return i + 1;
}

void quickSort(int *array, int p, int r)
{
    if (p < r)
    {
        int q = partition(array, p, r);
        quickSort(array, p, q - 1);
        quickSort(array, q + 1, r);
    }
}

int medianOfThree(int *array, int i, int j, int k)
{

    if (array[i] > array[j])
    {

        if (array[j] >= array[k])
        {
            return j;
        }
        else if (array[i] < array[k])
        {
            return i;
        }
        else
        {
            return k;
        }
    }
    else
    {

        if (array[i] >= array[k])
        {
            return i;
        }
        else if (array[j] < array[k])
        {
            return j;
        }
        else
        {
            return k;
        }
    }
}

int medianOfThreePartition(int *array, int p, int r)
{
    int mid = (p + r) / 2;
    int s = medianOfThree(array, p, r, mid);

    swapValue(array, s, r);

    int x = array[r];
    int i = p - 1;

    int j;
    for (j = p; j < r; j++)
    {
        if (array[j] <= x)
        {
            i = i + 1;
            swapValue(array, i, j);
        }
    }
    swapValue(array, i + 1, r);

    return i + 1;
}

void medianOfThreeQuickSort(int *array, int p, int r)
{
    if (p < r)
    {
        int q = medianOfThreePartition(array, p, r);
        medianOfThreeQuickSort(array, p, q - 1);
        medianOfThreeQuickSort(array, q + 1, r);
    }
}