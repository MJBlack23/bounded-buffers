#ifndef BUFFER_H
#define BUFFER_H

// Declare the buffer size
#define BUFFER_SIZE 10
// Declare a helper to tell the semaphore to use threads instead of processesf
#define USE_PTHREADS 0

typedef int buffer_item;

void init_buffer();
void insert_item();
buffer_item remove_item();

#endif