/* pthread */
#include <stdio.h>
#include <pthread.h>

int min,max,n,arr[20],tmp,i;
float avg;

void *cal_avg(){
    int sum = 0;
    for(i=0; i< n; i++){
        sum += arr[i];
    }
    avg = sum/n;
}

void *cal_min(){
    min = 0;
    for(i=1; i< n; i++){
        if (arr[0] > arr[i]) {
            arr[0] = arr[i];
        }
    }
    min = arr[0];
    arr[0] = tmp;
}

void *cal_max()
{
    max = 0;
    for(i=1; i< n; i++){
        if (arr[0] < arr[i]) {
            arr[0] = arr[i];
        }
    }
    max = arr[0];
    arr[0] = tmp;
}

void main()
{
    printf("Number of set: ");
    scanf("%d",&n);
    for(i=0; i< n; i++){
        printf("num %d : ",i+1);
        scanf("%d",&arr[i]);
    }
    tmp = arr[0];
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1, NULL, cal_avg, NULL);
    pthread_join(tid1, NULL);
    pthread_create(&tid2, NULL, cal_min, NULL);
    pthread_join(tid2, NULL);
    pthread_create(&tid3, NULL, cal_max, NULL);
    pthread_join(tid3, NULL);

    printf("Average is %f\n",avg);
    printf("Min is %d\n",min);
    printf("Max is %d\n",max);
    pthread_exit(0);
}
