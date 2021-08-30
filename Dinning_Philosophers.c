/* referance : https://www.alltestanswers.com/the-dining-philosophers-problem-by-implementing-a-solution-using-pthreads-mutex-locks-and-condition-variables/ */

#include <pthread.h>
#include <stdio.h>
#include <time.h>

/* max time to sleep */
#define MAX_SLEEP_TIME 5

/* จำนวนนักปราชญ์ */
#define NUMBER 5

/* สถานะของนักปราชญ์ */
enum{THINKING, HUNGRY, EATING} state[NUMBER];

/* thread id แต่ละคน */
int thread_id[NUMBER];

/* condition vars & mutex lock */
pthread_cond_t cond_vars[NUMBER];
pthread_mutex_t mutex_lock;

pthread_t tid[NUMBER];

void init(){
    int i;
    for(i=0; i<NUMBER; i++){
        state[i] = THINKING;
        thread_id[i] = i;
        pthread_cond_init(&cond_vars[i],NULL);
    }
    pthread_mutex_init(&mutex_lock,NULL);
}


void *philosopher(void *param){
    int *lnumber = (int *)param;
    int num = *lnumber;
    int sleep_time;
    int time_through_loop = 0;

    srandom((unsigned)time(NULL));

    while(time_through_loop < 5){
        sleep_time = (int)((random() %MAX_SLEEP_TIME) + 1);
        thinking(sleep_time);

        pickup_forks(num);
        
        printf("Philosopher %d is eating\n",num);

        sleep_time = (int)((random() %MAX_SLEEP_TIME) + 1);
        eating(sleep_time);

        printf("Philosopher %d is thinking\n",num);
        return_forks(num);

        time_through_loop++;
    }
}

void create_philosophers(){
    int i;
    for(i=0; i<NUMBER; i++){
        pthread_create(&tid[i],0,*philosopher,(void *)&thread_id[i]);        
    }
}

void eating(int sleep_time){
    sleep(sleep_time);
}

void thinking(int sleep_time){
    sleep(sleep_time);
}

/* dinning */
/* return ว่าคนทางขวาคือใคร */
int left_neighbor(int num){
    if (num == 0)
        return NUMBER - 1;
    else
        return num + 1;
}

/* return ว่าคนทางซ้ายคือใคร */
int right_neighbor(int num){
    if (num == NUMBER - 1)
        return 0;
    else
        return num + 1;
}

/* เช็คเงื่อนไขว่า ถ้าฉันหิว และคนข้างซ้าย-ขวาไม่ได้อยู่ในสถานะกิน ฉันกิน */
void test(int i){
    if ( (state[left_neighbor(i)] != EATING) && (state[i] == HUNGRY) && (state[right_neighbor(i)] != EATING) ){
        state[i] = EATING;
        pthread_cond_signal(&cond_vars[i]);
    }
}

void pickup_forks(int num){
    pthread_mutex_lock(&mutex_lock);
    state[num] = HUNGRY;
    test(num);
    while (state[num] != EATING){
        pthread_cond_wait(&cond_vars[num], &mutex_lock);
    }
    pthread_mutex_unlock(&mutex_lock);
}


void return_forks(int num){
    pthread_mutex_lock(&mutex_lock);
    state[num] = THINKING;
    test(left_neighbor(num));
    test(right_neighbor(num));
    pthread_mutex_unlock(&mutex_lock);
}


    
void main(){
    int i;
    init();
    create_philosophers();
    for(i=0; i<number; i++){
        pthread_join(tid[i],NULL);
    }
}
