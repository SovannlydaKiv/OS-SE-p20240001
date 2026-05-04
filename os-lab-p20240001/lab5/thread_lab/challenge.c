#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig) {
    keep_running = 0;
}

void *worker(void *arg) {
    pthread_t tid = pthread_self();
    while (keep_running) {
        printf("Thread ID: %lu is running\n", (unsigned long)tid);
        sleep(1);
    }
    printf("Thread ID: %lu exiting\n", (unsigned long)tid);
    pthread_exit(NULL);
}

int main() {
    signal(SIGINT, handle_sigint);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads cleanly exited. Goodbye.\n");
    return 0;
}