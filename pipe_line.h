#ifndef OS_EX5_PIPE_LINE_H
#define OS_EX5_PIPE_LINE_H

#include <stdbool.h>
#include "queue.h"
#include "active_object.h"

typedef struct {
    int number;
    bool is_prime;
    int seed;
} task_t;

void task1(void *arg);

void task2(void *arg);

void task3(void *arg);

void task4(void *arg);

void setup_pipeline(int N, int seed);

void stop_pipeline();


#endif //OS_EX5_PIPE_LINE_H
