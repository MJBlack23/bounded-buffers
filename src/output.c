#include <stdio.h>

void fatal(char message[], int err) {
    printf("%s\n", message);
    printf("Error Number: %d\n", err);
    exit(1);
}
