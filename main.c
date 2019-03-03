#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "src/input.h"
#include "src/helpers.h"
#include "src/buffer.h"

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

    // Initialize the random number generator
    initRNG();


    
    sleep(sleepTimeout);
    return 0;
}



void *producer(void) {
    int n;
    int shouldSleep = 0;
    
    do {
        if (shouldSleep) {
            sleep(randomNumber(3));

            // update the boolean to work next cycle
            shouldSleep = 0;
        } else {
            // produce an integer
            n = randomNumber(100);

            // declare a wait on the empty semaphore
            // acquire the mutex lock

            // add n to the buffer

            // release the mutex lock
            // signal: increment the full semaphore

            // Update the boolean to sleep next cycle
            shouldSleep = 1;
        }
        
    } while (1);
}

void *consumer(void) {
    int shouldSleep = 1;

    do {
        if (shouldSleep) {
            sleep(randomNumber(3));

            shouldSleep = 0;
        } else {
            // declare a wait on the full semaphore
            // acquire the mutex lock

            // remove an item from a buffer

            // release the mutex lock
            // signal: increment the empty semaphore

            // print the random int
        }
    } while (1);
}