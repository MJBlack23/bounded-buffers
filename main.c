#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>
#include <errno.h>

#include "src/buffer.h"
#include "src/helpers.h"
#include "src/input.h"
#include "src/output.h"

void *producer(void *params);
void *consumer(void *params);

int main(int argc, char *argv[]) {
    /**
     * Args
     * argv[1] = sleep time in main
     * argv[2] = # producer threads
     * argv[3] = # consumer threads
     **/
    if (verifyArgs(argc, argv) < 0) {
        exit(1);
    }

    // Print the welcome message
    print_welcome();

    // Initialize the random number generator
    initRNG();

    // Initialize the buffer
    init_buffer();
    print_time();
    printf("Buffer initialization Complete.\n");

    int i;
    // Initialize the producer threads
    for (i = 1; i <= producer_count; i++) {
        pthread_t tid; // pthread thread id
        pthread_attr_t attr; // pthread attributes
        if (pthread_attr_init(&attr) == -1) {
            fatal("Failed to initialize attributes for a producer thread...", errno);
        }

        // create the input number of producers
        if (pthread_create(&tid, &attr, producer, NULL) == -1) {
            fatal("Failed to create a thread for a producer...", errno);
        }
    }

    int c;
    // Initialize the consumer threads
    for (c = 1; c <= consumer_count; c++) {
        pthread_t tid; // pthread thread id
        pthread_attr_t attr; // pthread attributes
        if (pthread_attr_init(&attr) == -1) {
            fatal("Failed to initialize attributes for a consumer thread...", errno);
        }

        // create the input number of consumers
        if (pthread_create(&tid, &attr, consumer, NULL) == -1) {
            fatal("Failed to create a thread for a consumer...", errno);
        }
    }


    // Sleep for the designated time
    sleep(sleep_timeout);
    return 0;
}


// Create a producer that cretes items for the buffer
void *producer(void *param) {
    // init a buffer item to write into
    buffer_item n;
    // init sleep to false
    int should_sleep = 0;
    
    do {
        if (should_sleep) {
            // Sleep for 1 - 3 seconds
            sleep(randomNumber(5));

            // update the boolean to work next cycle
            should_sleep = 0;
        } else {
            // produce an integer
            n = randomNumber(-1);

            // insert item into the buffer
            insert_item(n);

            // update sleep to true for next loop
            should_sleep = 1;
        }
        
    } while (1);
}

// Create a consumer that consumes items from the buffer
void *consumer(void *param) {
    // init a buffer item to read into
    buffer_item n;
    // init sleep to true
    int should_sleep = 1;

    do {
        if (should_sleep) {
            // Sleep for 1 - 5 seconds
            sleep(randomNumber(5));

            // update shouldSleep to false
            should_sleep = 0;
        } else {
            // Retrieve an item from the buffer
            n = remove_item();

            // update shouldSleep to true
            should_sleep = 1;
        }
    } while (1);
}