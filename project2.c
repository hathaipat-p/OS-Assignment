#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static int list[50];
int listLength = sizeof(list)/sizeof(int);
int numThread = 3;

void *SortList(void *param);
void PrintList();

typedef struct args {
    int* arr;
    int threadNumber;
    int start;
    int stop;
} args;

/* C implementation QuickSort by GeeksforGeeks*/
void swap(int* a, int* b) {  // swap two elements
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot 
*/
int partition (int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int i = (low - 1);  // Index of smaller element

    for (int j = low; j <= high- 1; j++) {
        // if current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) { // main function that implements QuickSort
    if (low < high) {
        /* pi is partitioning index, arr[p] is now at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void Merge(int firstStart, int firstStop,int secondStart, int secondStop) {
    int temp[(firstStop-firstStart+1) + (secondStop-secondStart+1)];
    int runner1 = firstStart;
    int runner2 = secondStart;

    int i = 0;
    while(runner1 <= firstStop  && runner2 <= secondStop) {
        if(list[runner1] < list[runner2]) {
            temp[i] = list[runner1];
            runner1 += 1;
        }
        else {
            temp[i] = list[runner2];
            runner2 += 1;
        }
        i++;
    };
    while(runner1 <= firstStop) {
        temp[i] = list[runner1];
        runner1++;
        i++;
    }
    while(runner2 <= secondStop) {
        temp[i] = list[runner2];
        runner2++;
        i++;
    }

    int tempLength = sizeof(temp)/sizeof(int);
    for(int j=0;j<tempLength;j++) {
        list[j] = temp[j];
    }
}

void *MergeList(void) {
    int eachThread = listLength/numThread;

    for(int i=0;i<numThread-1;i++) {
        int firstStart = 0;
        int firstStop = (eachThread * (i+1))-1;
        int secondStart = eachThread * (i+1);
        int secondStop = (eachThread * (i+2))-1;
        if(i == numThread-1) {
            secondStop = listLength-1;
        }

        Merge(firstStart, firstStop, secondStart, secondStop);
    }
    pthread_exit(1);
}

int main(int argc, char *argv[]) {
    numThread = atoi(argv[1]);

    for(int i=0; i<listLength; i++) {
        list[i] = rand() % listLength;
    }
    printf("list length = %d\n", listLength);
    printf("number of thread = %d\n", numThread);
    printf("Before sort: \n");
    PrintList();

    int eachThread = listLength/numThread;
    pthread_t sortThread[numThread], mergeThread0;

    args arg[numThread];
    for(int i=0;i<numThread;i++) {
        arg[i].threadNumber = i;
        arg[i].start = (eachThread * i);
        arg[i].stop = (eachThread * (i+1)) - 1;
    }
    arg[numThread-1].stop += listLength - (eachThread * numThread);

    for(int i = 0;i<numThread;i++) {
        pthread_create(&sortThread[i], NULL, SortList, &arg[i]);
    }
    for(int i = 0;i<numThread;i++) {
        pthread_join(sortThread[i], NULL);
    }

    pthread_create(&mergeThread0, NULL, MergeList, NULL);
    pthread_join(mergeThread0, NULL);

    printf("After sort:\n");
    PrintList();
}

void *SortList(void *param) {
    args* ptr = (args*)param;
    int start = ptr->start;
    int stop = ptr->stop;

    if(ptr->threadNumber == 0) {
        printf("\n");
    }
    printf("init threadnum = %d, start = %d, stop = %d\n", ptr->threadNumber, start, stop);
    quickSort(list, start, stop);
    pthread_exit(0);
}

void PrintList() {
    for(int i=0; i<sizeof(list)/4; i++) {
        if((i+1) >= (sizeof(list)/4)) {
            printf("%i \n", list[i]);
        }
        else {
            printf("%i ", list[i]);
        }
    }
}