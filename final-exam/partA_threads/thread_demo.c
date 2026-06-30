#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>

void* worker(void* arg) {
    long id = (long)arg;
    long result = id * 10;
    printf("Worker thread %ld running, computed value: %ld\n", id, result);
    return (void*)result;
}

int main() {
    pthread_t threads[4];
    long total_sum = 0;
    
    // Create exactly 4 worker threads
    for(long i = 1; i <= 4; i++) {
        pthread_create(&threads[i-1], NULL, worker, (void*)i);
    }
    
    // Pause for 5 seconds so we can capture the kernel mapping for Task A2!
    sleep(5);
    
    // Join threads and collect results
    for(int i = 0; i < 4; i++) {
        void* res;
        pthread_join(threads[i], &res);
        total_sum += (long)res;
    }
    
    printf("All 4 threads joined. Total summary: %ld\n", total_sum);
    return 0;
}
