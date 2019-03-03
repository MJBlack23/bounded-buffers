#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fatal(char message[], int err) {
    printf("%s\n", message);
    printf("Error Number: %d => %s\n", err, strerror(err));
    exit(1);
}
