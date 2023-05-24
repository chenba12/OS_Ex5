#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "queue.h"

typedef void (*TaskFunction)(void*);

typedef struct {
    Queue* queue;
    pthread_t thread;
    TaskFunction func;
    int active;
} ActiveObject;

void* active_object_thread(void* arg) {
    ActiveObject* activeObj = (ActiveObject*)arg;

    while (1) {
        void* task = queue_pop(activeObj->queue);
        if (task != NULL) {
            activeObj->func(task);
        } else {
            pthread_mutex_lock(&activeObj->queue->mutex);
            int stop = !(activeObj->active);
            pthread_mutex_unlock(&activeObj->queue->mutex);

            if (stop) {
                break;
            }
        }
    }

    pthread_exit(NULL);
}

void create_active_object(ActiveObject* activeObj, Queue* queue, TaskFunction func) {
    activeObj->queue = queue;
    activeObj->func = func;
    activeObj->active = 1;

    pthread_create(&activeObj->thread, NULL, active_object_thread, activeObj);
    pthread_detach(activeObj->thread);
}

Queue* get_queue(ActiveObject* activeObj) {
    return activeObj->queue;
}

void stop(ActiveObject* activeObj) {
    activeObj->active = 0;
    pthread_cond_broadcast(&activeObj->queue->cond);  // Signal waiting threads to exit
    pthread_join(activeObj->thread, NULL);

    pthread_mutex_lock(&activeObj->queue->mutex);

    while (activeObj->queue->count > 0) {
        pthread_cond_wait(&activeObj->queue->cond, &activeObj->queue->mutex);
    }

    pthread_mutex_unlock(&activeObj->queue->mutex);
}

// Test function for demonstration

void task_function(void* task) {
    int* value = (int*)task;
    printf("Task processed: %d\n", *value);
    free(value);
}

int main() {
    ActiveObject activeObj;
    Queue queue;

    queue_init(&queue);
    create_active_object(&activeObj, &queue, task_function);

    // Enqueue some tasks
    for (int i = 1; i <= 5; i++) {
        int* value = malloc(sizeof(int));
        *value = i;
        queue_push(&queue, value);
    }

    printf("Before stopping active object\n");
    stop(&activeObj);
    printf("After stopping active object\n");

    return 0;
}