#include <stdio.h>
#include <pthread.h>
#include "queue.h"

/**
 * create a new queue
 * @param queue
 */
void queue_init(Queue *queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->cond, NULL);

}
/**
 * push a new item to the queue
 * @param queue
 * @param item
 */
void queue_push(Queue *queue, void *item) {
    pthread_mutex_lock(&queue->mutex);

    while (queue->count >= QUEUE_SIZE) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->data[queue->rear] = item;
    queue->count++;

    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
}

/**
 * remove the top item of the queue
 * @param queue
 */
void *queue_pop(Queue *queue) {
    pthread_mutex_lock(&queue->mutex);

    while (queue->count <= 0) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    void *item = queue->data[queue->front];
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->count--;

    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);

    return item;
}
