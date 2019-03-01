#include <pthread.h>
#include <semaphore.h>

#include "output.h"

#define BUFFER_SIZE 10
#define USE_PTHREADS 0

typedef struct Buffers {
    int buffer[BUFFER_SIZE];
    pthread_mutex_t mutex;
    sem_t full;
    sem_t empty;
} Buffer;

static Buffer buffer;
int errno = 0;

void init_buffer() {
    // Initialize the pthread mutex
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


int insert_item(int n) {
    if (sem_wait(&(buffer.empty)) == -1) {
        fatal("Failed to lock the empty semaphore...", errno);
    }

    pthread_mutex_lock(&(buffer.mutex));
    int insert_at;
    sem_getvalue(&(buffer.empty), insert_at);

    // insert the number
    buffer.buffer[insert_at] = n;

    pthread_mutex_unlock(&(buffer.mutex));

    if (sem_post(&(buffer.full)) == -1) {
        fatal("Failed to unlock the full semaphore...", errno);
    }

    return 0;
}

int remove_item() {
    if (sem_wait(&(buffer.full)) == -1) {
        fatal("Failed to lock the empty semaphore...", errno);
    }

    pthread_mutex_lock(&(buffer.mutex));
    // remove the number
    pthread_mutex_unlock(&(buffer.mutex));

    if (sem_post(&(buffer.empty)) == -1) {
        fatal("Failed to unlock the empty semaphore...", errno);
    }

    return 0;
}

int main() {
    return 0;
}