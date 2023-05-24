#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "pipe_line.h"

int main(int argc, char *argv[]) {
    // Checking arguments
    if (argc < 2 || argc > 3) {
        printf("Usage: %s N [seed]\n", argv[0]);
        return 1;
    }

    // Parse arguments
    int N = atoi(argv[1]);
    int seed = (argc == 3) ? atoi(argv[2]) : time(NULL);

    setup_pipeline(N, seed);

    sleep(1);

    stop_pipeline();

    return 0;
}