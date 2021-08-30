#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/* forks a child process that ultimately becomes a zombie process */

int main() {
    int pid = fork();

    if(pid < 0) {
        printf("Failed to fork\n");
        return -1;
    }
    if(pid > 0) { 
        // parent process
        printf("Parent process id: %d\n", getpid());
        sleep(10);
    }
    else { 
        // child process
        printf("Child process id: %d\n", getpid());
        exit(0);
    }

    return 0;
}
