#include <pthread.h>
#include <unistd.h>
#include "active_object.h"

/**
 * creates a new active object and create a new thread for it
 * @param activeObj the active object to init
 * @param queue the queue for the active object
 * @param func the function to execute
 */
void create_active_object(ActiveObject *activeObj, Queue *queue, TaskFunction func) {
    activeObj->queue = queue;
    activeObj->func = func;
    activeObj->active = 1;

    pthread_create(&activeObj->thread, NULL, active_object_thread, activeObj);
    pthread_detach(activeObj->thread);
}
/**
 * the thread loop of the active object
 * @param arg active object
 */
void *active_object_thread(void *arg) {
    ActiveObject *activeObj = (ActiveObject *) arg;

    while (1) {
        void *task = queue_pop(activeObj->queue);
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

/**
 * stops the active object
 * waits for it to finish whatever task it does and then close it
 * @param activeObj
 */
void stop(ActiveObject *activeObj) {
    activeObj->active = 0;
    pthread_cond_broadcast(&activeObj->queue->cond);  // Signal waiting threads to exit
    pthread_join(activeObj->thread, NULL);

    pthread_mutex_lock(&activeObj->queue->mutex);

    while (activeObj->queue->count > 0) {
        pthread_cond_wait(&activeObj->queue->cond, &activeObj->queue->mutex);
    }

    pthread_mutex_unlock(&activeObj->queue->mutex);
}