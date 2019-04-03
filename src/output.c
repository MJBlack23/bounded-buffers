#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_welcome() {
    printf(" Solution to the Producer-consumer Problem (aka Bounded-Buffer Problem)\n");
    printf(" For CIS-570\n");
    printf(" Written by Matt Black\n");

    printf("\n\n");
}

// helper to print an error message and exit
void fatal(char message[], int err) {
    printf("%s\n", message);
    printf("Error Number: %d => %s\n", err, strerror(err));
    exit(1);
}

// Helper to normalize the time to a two digit number
void pad_zero(int num, char *str) {
    if (num < 10) {
        sprintf(str, "0%d", num);
    } else {
        sprintf(str, "%d", num);
    }
}

// gets the current time and prints it in an easy to read manner
void print_time() {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    // format time
    char hour[3];
    char min[3];
    char sec[3];
    pad_zero(timeinfo->tm_hour, hour);
    pad_zero(timeinfo->tm_min, min);
    pad_zero(timeinfo->tm_sec, sec);
    
    

    printf("%d/%d/%d %s:%s:%s - ",
        timeinfo->tm_mon + 1,
        timeinfo->tm_mday,
        timeinfo->tm_year + 1900,
        hour,
        min,
        sec);
}
