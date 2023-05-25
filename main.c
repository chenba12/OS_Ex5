#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "pipe_line.h"

/**
 * Check for flags in the program first argument is the number of tasks to run
 * second flag is the seed of which the program will generate random numbers
 * start and stop the pipeline
 * @param argc
 * @param argv
 */
int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        printf("Usage: %s N [seed]\n", argv[0]);
        return 1;
    }

    // Parse arguments
    int N = atoi(argv[1]);
    int seed = (argc == 3) ? atoi(argv[2]) : time(NULL);

    setup_pipeline(N, seed);

    stop_pipeline();

    return 0;
}