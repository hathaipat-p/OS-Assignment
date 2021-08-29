/* fork() process */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
int n;

void main()
{   
    printf("Enter Number : ");
    scanf("%d",&n);

    pid_t pid;
    pid = fork();

    if (pid == 0) { /* child process */
        while(n != 1){
            if(n%2==0){
                n = n/2;
            }
            else{
                n = 3*n + 1;
            }
            printf("%d \n",n);
        }
    }
    else{
        /* waitting for child process */
        wait();
        printf("Process done\n");
    }
}
