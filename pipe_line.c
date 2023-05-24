#include <stdlib.h>
#include <stdio.h>
#include "pipe_line.h"
#include "utils.h"

ActiveObject ao1, ao2, ao3, ao4;
Queue queue1, queue2, queue3, queue4;

void task1(void *arg) {
    task_t *task = (task_t *) arg;
    task->number += 11;
    queue_push(&queue2, task);
}

void task2(void *arg) {
    task_t *task = (task_t *) arg;
    printf("%d\n", task->number);
    printf("%s\n", isPrime(task->number) ? "True" : "False");
    task->number -= 13;
    queue_push(&queue3, task);
}

void task3(void *arg) {
    task_t *task = (task_t *) arg;
    printf("%d\n", task->number);
    printf("%s\n", isPrime(task->number) ? "True" : "False");
    task->number += 2;
    queue_push(&queue4, task);
}

void task4(void *arg) {
    task_t *task = (task_t *) arg;
    printf("%d\n", task->number);
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
        task->number = (rand() % 900000) + 100000; // Generate a 6-digit number
        task->is_prime = isPrime(task->number);
        queue_push(&queue1, task);
    }
}

void stop_pipeline() {
    stop(&ao1);
    stop(&ao2);
    stop(&ao3);
    stop(&ao4);
}