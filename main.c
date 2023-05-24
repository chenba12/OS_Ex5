#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "pipe_line.h"

int main(int argc, char *argv[]) {
    // Parse command line arguments
    int N = atoi(argv[1]);
    int seed = argc > 2 ? atoi(argv[2]) : time(NULL);

    // Setup and start the pipeline
    setup_pipeline(N, seed);
    start_pipeline();

    // Wait for tasks to complete and then stop the pipeline
    sleep(N);
    stop_pipeline();

    return 0;
}