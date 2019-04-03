#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "buffer.h"

static time_t t;

// initialize the random number generator so numbers are random each run
void initRNG() {
    srand((unsigned) time(&t));
}

// random number generator returns buffer_item
buffer_item randomNumber(int max) {
    if (max < 0) {
        return (rand() % RAND_MAX);
    } else {
        return (rand() % max);
    }
}