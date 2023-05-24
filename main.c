#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "pipe_line.h"

int main(int argc, char *argv[]) {
    // Parse command line arguments
    if (argc > 3 || argc < 2) {
        printf("Usage: %s <num_threads>\n", argv[0]);
        return 1;
    }
    int num_threads = atoi(argv[1]);
    ActiveObject* activeObjs = malloc(num_threads * sizeof(ActiveObject));
    Queue queue;
    queue_init(&queue);

    for (int i = 0; i < num_threads; i++) {
        create_active_object(&activeObjs[i], &queue, task_function);
    }

    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, stdin) != -1) {
        int* value = malloc(sizeof(int));
        *value = atoi(line);
        queue_push(&queue, value);
    }
    free(line);

    for (int i = 0; i < num_threads; i++) {
        stop(&activeObjs[i]);
    }

    free(activeObjs);
    return 0;
}