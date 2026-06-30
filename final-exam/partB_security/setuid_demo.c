#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Real UID: %d, Effective UID: %d\n", getuid(), geteuid());
    return 0;
}
