#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "additional.h"

void outputArray(int *a, size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%lld ", a[i]);
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

_Bool isOrdered(const int *a, size_t n) {
    for (size_t i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1])
            return 0;
    }
    return 1;
}

void generateRandomArray(int *a, size_t size) {
    srand(time(0));
    for (size_t i = 0; i < size; i++)
        a[i] = 100000 - rand() % 100000;
}

void generateOrderedArray(int *a, size_t size) {
    for (size_t i = 0; i < size; ++i)
        a[i] = i;
}

void generateOrderedBackwards(int *a, size_t size){
    for (size_t i = size; i > 0; --i)
        a[i] = i;
}

void selectionSort(int *a, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < size; j++)
            if (a[j] < a[minPos])
                minPos = j;

        swap(&a[i], &a[minPos]);
    }
}

void insertionSort(int *a, size_t size) {
    for (size_t i = 1; i < size; i++) {
        int t = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > t) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
}

void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++)
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j])
                swap(&a[j - 1], &a[j]);
}

void combsort(int *a, const size_t size) {
    size_t step = size;
    _Bool isSwapped = 1;

    while (step > 1 || isSwapped) {
        if (step > 1)
            step /= 1.24733;
        isSwapped = 0;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                isSwapped = 1;
            }
    }
}

void shellSort(int *a, size_t size) {
    int buffer;
    for (size_t step = size / 2; step > 0; step /= 2)
        for (size_t i = step; i < size; i++) {
            buffer = a[i];
            size_t j;
            for (j = i; j >= step; j -= step) {
                if (buffer < a[j - step])
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = buffer;
        }
}

int digit(int n, int k, int N, int M) {
    return (n >> (N * k) & (M - 1));
}

void _radixSort(int *left, int *right, int N) {
    int roundingIntegers = (32 + N - 1) / N;
    int M = 1 << N;
    int size = right - left;

    int *b = (int *) malloc(sizeof(int) * size);
    int *c = (int *) malloc(sizeof(int) * M);

    for (int i = 0; i < roundingIntegers; i++) {
        for (int j = 0; j < M; j++)
            c[j] = 0;

        for (int *j = left; j < right; j++)
            c[digit(*j, i, N, M)]++;

        for (int j = 1; j < M; j++)
            c[j] += c[j - 1];

        for (int *j = right - 1; j >= left; j--)
            b[--c[digit(*j, i, N, M)]] = *j;

        int cur = 0;
        for (int *j = left; j < right; j++)
            *j = b[cur++];
    }
    free(b);
    free(c);
}

void radixSort(int *a, size_t n) {
    _radixSort(a, a + n, 8);
}


long long insertionSortN(int *a, size_t size) {
    long long countComp = 0;
    for (size_t i = 1; i < size && ++countComp; i++) {
        int t = a[i];
        size_t j = i;
        while (j > 0 && ++countComp && a[j - 1] > t && ++countComp) {
            a[j] = a[j - 1];
            j--;
        }
        a[j] = t;
    }
    return countComp;
}

long long bubbleSortN(int *a, size_t size) {
    long long countComp = 0;
    for (size_t i = 0; i < size - 1 && ++countComp; i++)
        for (size_t j = size - 1; j > i && ++countComp; j--)
            if (a[j - 1] > a[j] && ++countComp)
                swap(&a[j - 1], &a[j]);

    return countComp;
}

long long combsortN(int *a, const size_t size) {
    size_t step = size;
    int swapped = 1;
    long long countComp = 0;
    while (step > 1 && ++countComp || swapped && ++countComp) {
        if (step > 1 && ++countComp)
            step /= 1.24733;
        swapped = 0;
        for (size_t i = 0, j = i + step; j < size && ++countComp; ++i, ++j)
            if (a[i] > a[j] && ++countComp) {
                swap(&a[i], &a[j]);
                swapped = 1;
            }
    }
    return countComp;
}

long long shellSortN(int *a, size_t size) {
    long long countComp = 0;
    for (size_t step = size / 2; step > 0 && ++countComp; step /= 2)
        for (size_t i = step; i < size && ++countComp; i++) {
            int tmp = a[i];
            size_t j;
            for (j = i; j >= step && ++countComp; j -= step) {
                if (tmp < a[j - step] && ++countComp)
                    a[j] = a[j - step];
                else
                    break;
            }
            a[j] = tmp;
        }
    return countComp;
}






long long selectionSortN(int *a, size_t size) {
    long long countComp = 0;
    for (int i = 0; i < size - 1 && ++countComp; i++) {
        int minPos = i;
        for (int j = i + 1; j < size && ++countComp; j++)
            if (a[j] < a[minPos] && ++countComp)
                minPos = j;
        swap(&a[i], &a[minPos]);
    }
    return countComp;
}



