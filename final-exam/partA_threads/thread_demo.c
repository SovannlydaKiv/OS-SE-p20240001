#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

void* worker(void* arg) {
    long id = (long)arg;
    long result = id * 10;
    printf("Worker thread %ld running, computed value: %ld\n", id, result);
    return (void*)result;
}

void* extra_worker(void* arg) {
    printf("Extra worker %ld running...\n", (long)arg);
    sleep(2); // Pause so we can capture it in the process list!
    return (void*)((long)arg * 10);
}

int main() {
    pthread_t threads[4];
    long total_sum = 0;
    
    for(long i = 1; i <= 4; i++) { pthread_create(&threads[i-1], NULL, worker, (void*)i); }
    for(int i = 0; i < 4; i++) {
        void* res;
        pthread_join(threads[i], &res);
        total_sum += (long)res;
    }
    printf("--- Original 4 threads joined. ---\n");
    
    printf("\n[LWP MAPPING BEFORE] (Should be 1):\n");
    system("ps -eLf | grep thread_demo | grep -v grep");

    pthread_t extra_thread;
    pthread_create(&extra_thread, NULL, extra_worker, (void*)5);
    
    printf("\n[LWP MAPPING DURING] (Should be 2 - extra worker spawned!):\n");
    system("ps -eLf | grep thread_demo | grep -v grep");
    
    void* extra_res;
    pthread_join(extra_thread, &extra_res);
    total_sum += (long)extra_res;

    printf("\n[LWP MAPPING AFTER] (Should be back to 1 - extra worker joined):\n");
    system("ps -eLf | grep thread_demo | grep -v grep");
    
    printf("\nAll threads joined. Total summary: %ld\n", total_sum);
    return 0;
}
