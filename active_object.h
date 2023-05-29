#ifndef OS_EX5_ACTIVE_OBJECT_H
#define OS_EX5_ACTIVE_OBJECT_H

#include "queue.h"

typedef void (*TaskFunction)(void *);

typedef struct {
    Queue *queue;
    pthread_t thread;
    TaskFunction func;
    int active;
} ActiveObject;

void *active_object_thread(void *arg);

Queue *get_queue(ActiveObject *activeObj);

void CreateActiveObject(ActiveObject *activeObj, Queue *queue, TaskFunction func);

void stop(ActiveObject *activeObj);

#endif
