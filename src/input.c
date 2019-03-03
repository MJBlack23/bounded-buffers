#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern int sleep_timeout;
extern int producer_count;
extern int consumer_count;

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
    sleep_timeout = atoi(argv[1]);
    producer_count = atoi(argv[2]);
    consumer_count = atoi(argv[3]);

    return 0;
}