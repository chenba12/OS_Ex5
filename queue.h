#ifndef QUEUE_H
#define QUEUE_H

#include <bits/pthreadtypes.h>

#define QUEUE_SIZE 10

typedef struct {
    void *data[QUEUE_SIZE];
    int front;
    int rear;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Queue;

void queue_init(Queue *queue);

void queue_push(Queue *queue, void *item);

void *queue_pop(Queue *queue);

#endif
