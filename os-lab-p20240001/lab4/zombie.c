#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Child (PID %d): I'm exiting now.\n", getpid());
        exit(0);
    }

    printf("Parent: Child is now a zombie. Sleeping 40s...\n");
    sleep(40); 

    printf("Parent: Now calling wait() to clean up the zombie...\n");
    wait(NULL); 

    printf("Parent: Zombie should be gone. Sleeping 10s more so you can check.\n");
    sleep(10);
    return 0;
}