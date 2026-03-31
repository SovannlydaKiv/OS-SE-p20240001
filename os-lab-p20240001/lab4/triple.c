#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            printf("Child %d (PID %d) is sleeping...\n", i+1, getpid());
            sleep(30);
            exit(0);
        }
    }

    printf("Parent (PID %d) is waiting for 3 children. Run 'ps --forest' now!\n", getpid());
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }
    printf("All children finished.\n");
    return 0;
}