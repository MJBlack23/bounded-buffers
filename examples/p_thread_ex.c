#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum; // data to be shared by the thread
void *runner(void *param); // the thread

int main(int argc, char *argv []) {
    pthread_t tid; // thread id
    pthread_attr_t attr; // thread attributes

    if (argc != 2) {
        fprintf(stderr, "usage: a.out <integer value>\n");
        return -1;
    }

    if (atoi(argv[1]) < 0) {
        fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
        return -1;
    }

    // init the thread attributes
    pthread_attr_init(&attr);

    // create the thread
    pthread_create(&tid, &attr, runner, argv[1]);

    // wait for the thread to exit
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);
}

// the thread will being control in this function
void *runner(void *param) {
    int i, upper = atoi(param);
    sum = 0;

    for (i = 1; i <= upper; i++) {
        sum += i;
    }

    pthread_exit(0);
}