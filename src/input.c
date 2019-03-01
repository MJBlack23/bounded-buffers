#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern int sleepTimeout;
extern int producerCount;
extern int consumerCount;

int verifyArgs(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage a.out <timeout> <# producers> <# consumers>.\n");
        return -1;
    }

    int i;

    for (i = 1; i < 4; i++) {
        if (atoi(argv[i]) < 0)
        {
            fprintf(stderr, "%d must be >= 0\n", atoi(argv[i]));
            return -1;
        }
    }

    // Explicitly set args for readability
    sleepTimeout = atoi(argv[1]);
    producerCount = atoi(argv[2]);
    consumerCount = atoi(argv[3]);

    return 0;
}