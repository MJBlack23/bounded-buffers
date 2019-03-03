#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>
#include <errno.h>
#include "output.h"
#include "buffer.h"

typedef struct Buffers {
    int buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    sem_t full;
    sem_t empty;
} Buffer;

static Buffer buffer;

void init_buffer() {
    // Initialize the pthread mutex attributes
    pthread_mutexattr_t mutex_attr;


    if (pthread_mutexattr_init(&mutex_attr) == -1) {
        fatal("Failed to initialize mutex attributes...", errno);
    }
    if (pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED) == -1) {
        fatal("Failed to share the mutes across shared...", errno);
    }
    if (pthread_mutex_init(&(buffer.mutex), &mutex_attr) == -1) {
        fatal("Failed to initialize the mutex...", errno);
    }

    // initialize the full semaphore
    if (sem_init(&(buffer.full), USE_PTHREADS, 0) == -1) {
        fatal("Failed to initialize the full buffer...", errno);
    }

    // initialize the empty semaphore
    if (sem_init(&(buffer.empty), USE_PTHREADS, BUFFER_SIZE) == -1) {
        fatal("Failed to initialize the empty buffer...", errno);
    }
}


void insert_item(buffer_item n) {
    if (sem_wait(&(buffer.empty)) == -1) {
        fatal("Failed to lock the empty semaphore...", errno);
    }

    if (pthread_mutex_lock(&(buffer.mutex)) == -1) {
        fatal("Failed to lock the mutex...", errno);
    }

    // Determine where to insert the new number at by
    // getting the current value of the full semaphore
    int insert_at;
    sem_getvalue(&(buffer.full), &insert_at);

    // log what is happening
    printf("Inserting n %d at location %d\n", n, insert_at);

    // insert the number at the next location
    buffer.buffer[insert_at] = n;

    if (pthread_mutex_unlock(&(buffer.mutex)) == -1) {
        fatal("Failed to unlock the muxtex...", errno);
    }

    if (sem_post(&(buffer.full)) == -1) {
        fatal("Failed to unlock the full semaphore...", errno);
    }
}

buffer_item remove_item() {
    buffer_item n;

    if (sem_wait(&(buffer.full)) == -1) {
        fatal("Failed to lock the empty semaphore...", errno);
    }

    if (pthread_mutex_lock(&(buffer.mutex)) == -1) {
        fatal("Failed to lock the mutex...", errno);
    }

    // Figure out where to retrieve the next number by retieve the value of the empty mutex
    // The value will be at the empty mutex - the max buffer size - 1 (due to 0 based array)
    int remove_at;
    sem_getvalue(&(buffer.empty), &remove_at);
    remove_at = BUFFER_SIZE - 1 - remove_at;

    // remove the number
    n = buffer.buffer[remove_at];

    // log what is happening
    printf("Removing n %d at location %d\n", n, remove_at);

    if (pthread_mutex_unlock(&(buffer.mutex)) == -1) {
        fatal("Failed to unlock the muxtex...", errno);
    }

    if (sem_post(&(buffer.empty)) == -1) {
        fatal("Failed to unlock the empty semaphore...", errno);
    }

    return n;
}