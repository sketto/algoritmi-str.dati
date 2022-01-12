#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#define RAND_SEED 200

int *insertionSort(int array[], int length)
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

    return array;
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

int *mergeSort(int array[], int p, int r) {

    if(p < r) {

        int q = (p + r) / 2;
        mergeSort(array, p, q);
        mergeSort(array, q + 1, r);
        merge(array, p, q, r);
    }

    int n = sizeof(array) / sizeof(array[0]);
    printf("\nn: %d\n", n);

    int i;
    for(i = 0; i < n; i++) {

        printf("%d ", array[i]);

    }

    return array;
}

void merge(int array[], int p, int q, int r) {

    int n1 = q - p + 1;
    int n2 = r - q;

    int leftArray[n1];
    int rightArray[n2];
    int i, j;

    for(i = 0; i < n1; i++) {
        leftArray[i] = array[p + i - 1];

        for(j = 0; j < n2; j++) {
            rightArray[j] = array[q + j];
        }
    }

    i = 0;
    j = 0;

    int k;
    for(k = p; k < r; k++) {

        if( i <= n1) {

            if(j <= n2) {

                if(leftArray[i] <= rightArray[j]) {

                    //copyFromL(i);
                    array[k] = leftArray[i];
                } else {
                    //copyFromR(j);
                    array[k] = rightArray[j];

                }
            } else {
                //copyFromL(i);
                array[k] = leftArray[i];

            }
        } else {
            //copyFromR(j);
            array[k] = rightArray[j];
        }
    }
}

