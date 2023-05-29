#ifndef OS_EX5_PIPE_LINE_H
#define OS_EX5_PIPE_LINE_H

#include <stdbool.h>
#include "queue.h"
#include "active_object.h"

#define NO_Seed (-1)
typedef struct {
    int number;
    bool is_prime;
    int seed;
    int N;
} task_t;

void task1(void *arg);

void task2(void *arg);

void task3(void *arg);

void task4(void *arg);

void setupPipeline(int N, int seed);

void stopPipeline();


#endif //OS_EX5_PIPE_LINE_H
