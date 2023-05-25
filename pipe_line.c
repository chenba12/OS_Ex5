#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
        srand(task->seed);
        initialized = 1;
    }
    task->number = (rand() % 900000) + 100000;
    printf("Generated number: %d\n", task->number);
    usleep(1000);
    queue_push(&queue2, task);
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
    free(task);
}

void setup_pipeline(int N, int seed) {
    srand(seed);
    queue_init(&queue1);
    queue_init(&queue2);
    queue_init(&queue3);
    queue_init(&queue4);

    create_active_object(&ao1, &queue1, task1);
    create_active_object(&ao2, &queue2, task2);
    create_active_object(&ao3, &queue3, task3);
    create_active_object(&ao4, &queue4, task4);

    for (int i = 0; i < N; i++) {
        task_t *task = malloc(sizeof(task_t));
        queue_push(&queue1, task);
    }
}

void stop_pipeline() {
    stop(&ao1);
    stop(&ao2);
    stop(&ao3);
    stop(&ao4);

}