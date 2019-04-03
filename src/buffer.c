#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>
#include <errno.h>
#include "output.h"
#include "buffer.h"

// Declare a buffer type
typedef struct Buffers {
    buffer_item buffer[BUFFER_SIZE]; // buffer of BUFFER SIZE of buffer_item
    pthread_mutex_t mutex; // the mutex
    sem_t full; // the full semaphore
    sem_t empty; // the empty semaphore
} Buffer;

// init a global buffer variable
static Buffer buffer;

void init_buffer() {
    // Initialize the pthread mutex attributes
    pthread_mutexattr_t mutex_attr;

    // attempt to init the mutex attributes
    if (pthread_mutexattr_init(&mutex_attr) == -1) {
        fatal("Failed to initialize mutex attributes...", errno);
    }

    // attempt to set the mutex to be shared by processes
    if (pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED) == -1) {
        fatal("Failed to share the mutes across shared...", errno);
    }

    // initialize the mutex with the attributes
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

// Insert an item into the shared buffer
void insert_item(buffer_item n) {
    // attempt to lock the semaphore
    if (sem_wait(&(buffer.empty)) == -1) {
        fatal("Failed to lock the empty semaphore...", errno);
    }

    // attempt to lock the mutex
    if (pthread_mutex_lock(&(buffer.mutex)) == -1) {
        fatal("Failed to lock the mutex...", errno);
    }

    // Determine where to insert the new number at by
    // getting the current value of the full semaphore
    int insert_at;
    sem_getvalue(&(buffer.full), &insert_at);

    // log what is happening in the critical section
    print_time();
    printf("Inserting %d at location %d\n", n, insert_at);

    // insert the number at the next location
    buffer.buffer[insert_at] = n;

    // attempt to unlock the mutex
    if (pthread_mutex_unlock(&(buffer.mutex)) == -1) {
        fatal("Failed to unlock the muxtex...", errno);
    }

    // unlock the full sempahore
    if (sem_post(&(buffer.full)) == -1) {
        fatal("Failed to unlock the full semaphore...", errno);
    }
}

// remove and return an item from the shared buffer
buffer_item remove_item() {
    // init a buffer_item to be read into
    buffer_item n;

    // atempt to lock the full sempahore
    if (sem_wait(&(buffer.full)) == -1) {
        fatal("Failed to lock the empty semaphore...", errno);
    }

    // attempt to lock the mutex
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

    // log what is happening inside the critical section
    print_time();
    printf("Removing  %d at location %d\n", n, remove_at);

    // attempt to unlock the mutex
    if (pthread_mutex_unlock(&(buffer.mutex)) == -1) {
        fatal("Failed to unlock the muxtex...", errno);
    }

    // attemp to unlock the empty semaphore
    if (sem_post(&(buffer.empty)) == -1) {
        fatal("Failed to unlock the empty semaphore...", errno);
    }

    return n;
}