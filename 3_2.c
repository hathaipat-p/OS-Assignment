#include <stdio.h>
#include <unistd.h>

int main() {
    /* fork a child process */
    fork();

    /* fork another child process */
    fork();

    /* and fork another */
    fork();

    printf("pid %d, ppid %d\n", (int)getpid(), (int)getppid());
    return 0;
}