#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void handle_sig(int sig) {
    if (sig == SIGINT) {
        printf("\nCaught SIGINT (Interactive Interrupt). Cleaning up and exiting cleanly...\n");
    } else if (sig == SIGTERM) {
        printf("\nCaught SIGTERM (Polite Termination). Cleaning up and exiting cleanly...\n");
    }
    exit(0);
}

int main() {
    signal(SIGINT, handle_sig);
    signal(SIGTERM, handle_sig);
    printf("Signal demo running. PID: %d. Send Ctrl+C...\n", getpid());
    
    // Infinite loop to keep the program alive until interrupted
    while(1) {
        sleep(1);
    }
    return 0;
}
