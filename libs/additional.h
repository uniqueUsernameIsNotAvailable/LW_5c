//This function takes an array of integers and a size of the array as arguments. It then asks the user to input the values of the array.
void inputArray(int *a, size_t size);

//Printing out the array.
void outputArray(int *a, size_t size);

//This function swaps the values of the two integers that are passed in as arguments.
void swap(int *a, int *b);

//This function is checking if the array is ordered.
_Bool isOrdered(const int *a, size_t size);

//This function is generating an array of random integers.
void generateRandomArray(int *a, size_t size);

//This function is comparing two integers
int cmp(const void *a, const void *b);

//This function is comparing two integers and returning the opposite value of what `cmp` is returning.
int cmpReverse(const void *a, const void *b);

//This function is generating an array of integers that are in ascending order.
void generateOrderedArray(int *a, size_t size);

//This function is generating an array of integers that are in descending order.
void generateOrderedBackwards(int *a, size_t size);

//This function is sorting the array of integers in ascending order.
void selectionSort(int *a, size_t size);

void insertionSort(int *a, size_t size);

void bubbleSort(int *a, size_t size);

void combsort(int *a, size_t size);

void shellSort(int *a, size_t size);

void radixSort(int *a, size_t n);

long long insertionSortN(int *a, size_t size);

long long bubbleSortN(int *a, size_t size);

long long combsortN(int *a, size_t size);

long long shellSortN(int *a, size_t size);

long long selectionSortN(int *a, size_t size);
