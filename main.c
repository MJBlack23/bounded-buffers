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
        pthread_t tid;
        pthread_attr_t attr;
        if (pthread_attr_init(&attr) == -1) {
            fatal("Failed to initialize attributes for a producer thread...", errno);
        }

        if (pthread_create(&tid, &attr, producer, NULL) == -1) {
            fatal("Failed to create a thread for a producer...", errno);
        }
    }

    int c;
    // Initialize the consumer threads
    for (c = 1; c <= consumer_count; c++) {
        pthread_t tid;
        pthread_attr_t attr;
        if (pthread_attr_init(&attr) == -1) {
            fatal("Failed to initialize attributes for a consumer thread...", errno);
        }

        if (pthread_create(&tid, &attr, consumer, NULL) == -1) {
            fatal("Failed to create a thread for a consumer...", errno);
        }
    }


    // Sleep for the designated time
    sleep(sleep_timeout);
    return 0;
}



void *producer(void *param) {
    buffer_item n;
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

            insert_item(n);

            should_sleep = 1;
        }
        
    } while (1);
}


void *consumer(void *param) {
    buffer_item n;
    int should_sleep = 1;

    do {
        if (should_sleep) {
            // Sleep for 1 - 3 seconds
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