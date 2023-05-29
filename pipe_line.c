#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "pipe_line.h"
#include "utils.h"

ActiveObject ao1, ao2, ao3, ao4;
Queue queue1, queue2, queue3, queue4;

/**
 * First AO task
 * init the srand with the seed once
 * and generate random numbers
 * @param arg task data
 */
void task1(void *arg) {
    task_t *task = (task_t *) arg;

    static int initialized = 0;
    if (!initialized) {
        if (task->seed == NO_Seed) {
            srand(time(NULL));
        } else {
            srand(task->seed);
        }
        initialized = 1;
    }
    for (int i = 0; i < task->N; ++i) {
        task_t *new_task = malloc(sizeof(task_t));
        *new_task = *task;  // Copy contents of current task to new task
        new_task->number = (rand() % 900000) + 100000;
        printf("Generated number: %d\n", new_task->number);
        usleep(1);
        queue_push(&queue2, new_task);
    }
    free(task);
}

/**
 * Second AO task
 * check if the number is a prime number and add 11 to it
 * @param arg task data
 */
void task2(void *arg) {
    task_t *task = (task_t *) arg;
    printf("Number: %d\n", task->number);
    printf("Is prime: %s\n", isPrime(task->number) ? "True" : "False");
    task->number += 11;
    queue_push(&queue3, task);
}

/**
 * Third AO task check if the new number is a prime and subtract 13 from it
 * @param arg task data
 */
void task3(void *arg) {
    task_t *task = (task_t *) arg;
    printf("Number: %d\n", task->number);
    printf("Is prime: %s\n", isPrime(task->number) ? "True" : "False");
    task->number -= 13;
    queue_push(&queue4, task);
}

/**
 * Fourth AO task check if the new number is a prime and add 2 to it
 * we should be back at the starting number
 * free task
 * @param arg task data
 */
void task4(void *arg) {
    task_t *task = (task_t *) arg;
    printf("Received number: %d\n", task->number);
    task->number += 2;
    printf("End number: %d\n", task->number);
//    free(task);
}

void setupPipeline(int N, int seed) {
    queue_init(&queue1);
    queue_init(&queue2);
    queue_init(&queue3);
    queue_init(&queue4);

    CreateActiveObject(&ao1, &queue1, task1);
    CreateActiveObject(&ao2, &queue2, task2);
    CreateActiveObject(&ao3, &queue3, task3);
    CreateActiveObject(&ao4, &queue4, task4);

    task_t *task = malloc(sizeof(task_t));
    task->seed = seed;
    task->N = N;
    queue_push(&queue1, task);
}

void stopPipeline() {
    while (queue1.count > 0 || queue2.count > 0 || queue3.count > 0 || queue4.count > 0) {
        sleep(1);
    }
    stop(&ao1);
    stop(&ao2);
    stop(&ao3);
    stop(&ao4);
}