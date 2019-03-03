#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "buffer.h"

static time_t t;

void initRNG() {
    srand((unsigned) time(&t));
}

// random number generator
buffer_item randomNumber(int max) {
    if (max < 0) {
        return (rand() % RAND_MAX);
    } else {
        return (rand() % max);
    }
}