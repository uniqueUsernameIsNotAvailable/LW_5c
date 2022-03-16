#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "additional.h"

void inputArray(int *a, size_t size) {
    for (size_t i = 0; i < size; i++)
        scanf("%d", &a[i]);
}

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

int cmp(const void *a, const void *b) {
    return *(const int *) a - *(const int *) b;
}

int cmpReverse(const void *a, const void *b) {
    return *(const int *) b - *(const int *) a;
}

void generateOrderedArray(int *a, size_t size) {
    generateRandomArray(a, size);
    qsort(a, size, sizeof(int), cmp);
}

void generateOrderedBackwards(int *a, size_t size) {
    generateRandomArray(a, size);
    qsort(a, size, sizeof(int), cmpReverse);
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