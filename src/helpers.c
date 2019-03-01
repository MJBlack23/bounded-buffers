#include <stdlib.h>
#include <time.h>

static time_t t;

void initRNG() {
    srand((unsigned) time(&t));
}

// random number generator
int randomNumber(int max) {
    if (max < 0) {
        return (rand() % RAND_MAX);
    } else {
        return (rand() % max);
    }
}