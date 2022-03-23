#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "libs/additional.h"

#define TIME_TEST(testCode, time) { \
    clock_t start_time = clock(); \
    testCode \
        clock_t end_time = clock(); \
    clock_t sort_time = end_time - start_time; \
    time = (double) sort_time / CLOCKS_PER_SEC; \
    }

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
//--------------------------------------------- SETTING UP CORE FUNCTIONS
// функция сортировки
typedef struct SortFunc {
    void (*sort)(int *a, size_t n);    // указатель на функцию сортировки
    char name[64];                     // имя сортировки, используемое при выводе
} SortFunc;

// функция счёта сравнений
typedef struct CompCountFunc {
    long long (*nComp)(int *a, size_t n);

    char name[64];
} CompCountFunc;

// функция генерации
typedef struct GeneratingFunc {
    void (*generate)(int *a, size_t n); // указатель на функцию генерации последоват.
    char name[64];                      // имя генератора, используемое при выводе
} GeneratingFunc;

double getTime() {
    clock_t start_time = clock();
// фрагмент кода
// время которого измеряется
    clock_t end_time = clock();\
clock_t sort_time = end_time - start_time;
    return (double) sort_time / CLOCKS_PER_SEC;
}


void checkTime(void (*sortFunc )(int *, size_t), void (*generateFunc )(int *, size_t), size_t size, char *experimentName) {
    static size_t runCounter = 1;

    static int innerBuffer[200000];
    generateFunc(innerBuffer, size);
    printf("Run #% zu| ", runCounter++);
    printf(" Name : %s\n", experimentName);

    double time;
    TIME_TEST ({ sortFunc(innerBuffer, size); }, time);
    printf(" Status : ");

    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time : %.3 f s.\n", time);
        char filename[256];
        sprintf(filename, "./data/%s.csv ", experimentName);
        FILE *f = fopen(filename, "a");

        if (f == NULL) {
            printf(" FileOpenError %s", filename);
            exit(1);
        }

        fprintf(f, "%zu; %.3 f\n", size, time);
        fclose(f);
    } else {
        printf(" Wrong !\n");
        outputArray(innerBuffer, size);
        exit(1);
    }
}

void checkNComp(long long (*nComp )(int *a, size_t n), void (*generateFunc)(int *, size_t), size_t size,
                char *experimentName, char *name) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[50000000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf("Name: %s\n", experimentName);

    long long nComps = nComp(innerBuffer, size);

    printf("Status: ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Comps: %lld\n", nComps);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/second/%s.csv", experimentName);
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf("FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %lld\n", size, nComps);
        fclose(f);
    } else {
        printf("Wrong!\n");

        outputArray(innerBuffer, size);

        exit(1);
    }
}

GeneratingFunc generatingFuncs[] = {
 //       {generateRandomArray,      "random"},
        {generateOrderedArray,     "ordered"},
  //      {generateOrderedBackwards, "orderedBackwards"}
};

void timeExperiment() {
    SortFunc sorts[] = {
            //{selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            //{bubbleSort, "bubbleSort"},
           // {combsort, "combsort"},
          //  {shellSort, "shellSort"},
           // {radixSort, "radixSort"},
// вы добавите свои сортировки
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);

    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    for (size_t size = 10000000; size <= 50000000; size += 10000000) {
        printf(" ------------------------------\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++)
            for (int j = 0; j < CASES_N; j++) {
                static char filename[128];
                sprintf(filename, "%s_% s_time",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort, generatingFuncs[j].generate, size, filename);
            }
    }

    printf("\n");
}


void compExperiment() {
    CompCountFunc nComps[] = {
//            {selectionSortN, "selectionSortN"},
//            {insertionSortN, "insertionSortN"},
//            {bubbleSortN,    "bubbleSortN"},
            {combsortN, "combSortN"},
//            {shellSortN,     "shellSortN"},
    };

    const unsigned COMPS_N = ARRAY_SIZE(nComps);
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 1000; size <= 10000; size += 1000) {
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
        printf("Size : %d\n", size);
        for (int i = 0; i < COMPS_N; i++)
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_comps",
                        nComps[i].name, generatingFuncs[j].name);
                checkNComp(nComps[i].nComp,
                           generatingFuncs[j].generate,
                           size, filename, nComps[i].name);
            }

        printf("\n");
    }
}

int main() {
    timeExperiment();
    //compExperiment();

    return 0;
}

