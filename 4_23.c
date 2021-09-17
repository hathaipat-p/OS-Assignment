#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

int numThread = 2;
int input;
int primeArr[] = {};
int arr1[] = {}, arr2[] = {};

typedef struct args {
    int* arr;
    int threadNumber;
    int start;
    int stop;
} args;

bool valueInArr(int val, int arr[]) {
    for(int i = 0; i < sizeof(arr); i++) {
        if(arr[i] == val)
            return true;
    }
    return false;
}

void* FindPrimeNum(void *param) {
    int i, num, arrSize = 0;
    int prime_arr[] = {};

    for (i=2; i<=input; ++i) {
        for(num=2; num<=i/2; ++num) {
            if (i%num != 0 && !valueInArr(num, prime_arr)) {
                prime_arr[arrSize] = num;
                arrSize++;
            }
        }
    }
    pthread_exit(prime_arr);
}

int main(int argc, char *argv[]) {
    input = atoi(argv[1]);

    //pthread_t firstThread, secondThread;
    //pthread_create(&firstThread, NULL, FindPrimeNum, NULL);
    //pthread_create(&secondThread, NULL, FindPrimeNum, NULL);
    
    //pthread_join(firstThread, &arr1);
    //pthread_join(secondThread, &arr2);

    int eachThread = input/numThread;
    pthread_t thread[numThread], mergeThread0;

    args arg[numThread];
    for(int i=0;i<numThread;i++) {
        arg[i].threadNumber = i;
        arg[i].start = (eachThread * i);
        arg[i].stop = (eachThread * (i+1)) - 1;
    }
    arg[numThread-1].stop += input - (eachThread * numThread);

    for(int i = 0;i<numThread;i++) {
        pthread_create(&thread[i], NULL, FindPrimeNum, &arg[i]);
    }

    pthread_join(thread[0], &arr1);
    pthread_join(thread[1], &arr2);

    printf("Prime numbers which less than or equal to %d:\n", input);

    for(int j = 0; j < (int)(sizeof(arr1)/sizeof(int)); j++) {
        printf(" %d ", arr1[j]);
    }

    return 0;
}