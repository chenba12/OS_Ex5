#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "queue.h"

void queue_init(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);

}

void queue_destroy(Queue *queue) {
    pthread_mutex_lock(&queue->mutex);
    pthread_cond_destroy(&queue->cond);
    pthread_mutex_destroy(&queue->mutex);
    pthread_mutex_unlock(&queue->mutex);
}

void queue_push(Queue *queue, void *item) {
    pthread_mutex_lock(&queue->mutex);

    // Wait if the queue is full
    while (queue->count >= QUEUE_SIZE) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->data[queue->rear] = item;
    queue->count++;

    pthread_cond_signal(&queue->cond); // Signal waiting threads that an item has been added
    pthread_mutex_unlock(&queue->mutex);
}

void *queue_pop(Queue *queue) {
    pthread_mutex_lock(&queue->mutex);

    // Wait if the queue is empty
    while (queue->count <= 0) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    void *item = queue->data[queue->front];
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->count--;

    pthread_cond_signal(&queue->cond); // Signal waiting threads that an item has been removed
    pthread_mutex_unlock(&queue->mutex);

    return item;
}
