#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define RAND_SEED 200
#define K 100

void adaptedInsertionSort(int *array, int p, int r)
{
    int j;
    int i;
    int key;

    for (j = p + 1; j <= r; j++)
    {
        key = array[j];
        i = j - 1;

        while (i >= p && array[i] > key)
        {
            array[i + 1] = array[i];
            i = i - 1;
        }

        array[i + 1] = key;
    }
}

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
    int *vet = malloc(length * sizeof(int)); // per evitare "warning: function returns address of local variable" è utile allocare la memoria dinamicamente
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

    int n1 = q - p + 1;
    int n2 = r - q;

    int arrL[n1], arrR[n2], i, j;

    for (i = 0; i < n1; i++)
    {
        arrL[i] = array[p + (i + 1) - 1];
    }

    for (j = 0; j < n2; j++)
    {
        arrR[j] = array[q + (j + 1)];
    }

    i = 0;
    j = 0;

    int k;
    for (k = p; k <= r; k++)
    {
        if (i < n1)
        {
            if (j < n2)
            {
                if (arrL[i] <= arrR[j])
                {
                    array[k] = arrL[i];
                    i++;
                }
                else
                {
                    array[k] = arrR[j];
                    j++;
                }
            }
            else
            {
                array[k] = arrL[i];
                i++;
            }
        }
        else
        {
            array[k] = arrR[j];
            j++;
        }
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

        // insertionSort(array, length);
        adaptedInsertionSort(array, p, r);
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

double singleExperiment(int length, int maxInstances, int alg)
{

    int *array;
    int i, j;
    clock_t t_tot = 0;

    for (i = 0; i < maxInstances; i++)
    {

        clock_t t_start, t_end, t_elapsed;

        array = generateRandomArray(length);

        // int index;
        //  printf("random array:\n");
        //  for (index = 0; index < length; index++)
        //  {
        //      printf(" %d ", array[index]);
        //  }
        //  printf("\n");

        if (alg == 1) // IS
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
        else if (alg == 2) // MG
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
        else if (alg == 3) // HS
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
        else if (alg == 4) // QS con mediana di tre
        {
            t_start = clock();

            medianOfThreeQuickSort(array, 0, length - 1);

            t_end = clock();
        }

        t_elapsed = t_end - t_start;
        t_tot = t_tot + t_elapsed;
    }

    double t_final = (double)t_tot / (double)maxInstances;

    return t_final;
}

void experiment(int minLength, int maxLength)
{

    int maxInstances = 5;
    int step = 5;
    double timeIS, timeMS, timeHS, timeQS_M3;
    int length;

    for (length = minLength; length <= maxLength; length += step)
    {
        timeIS = singleExperiment(length, maxInstances, 1);
        timeMS = singleExperiment(length, maxInstances, 2);
        timeHS = singleExperiment(length, maxInstances, 3);
        timeQS_M3 = singleExperiment(length, maxInstances, 4);

        // IS; MS; HS; QS_M3; DIM
        printf(" %f; %f; %f; %f; %d\n", timeIS, timeMS, timeHS, timeQS_M3, length);
    }
}

int main()
{
    // experiment(1000, 50000);
    //  int array[10] = {5, 9, 4, 0, 3, 12, 56, 90, 11, 34};
    // mergeSort(array, 0, 9);
    experiment(5, 1500);

    return 0;
}