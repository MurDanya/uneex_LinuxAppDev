#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct range {
    int start;
    int stop;
    int step;
    int iter;
} range;

void argparse(int argc, char *argv[], int *start, int *stop, int *step) {
    if (argc <= 1) {
        printf("HELP:\n");
        printf("range STOP -- print a sequence [0, ..., STOP-1]\n");
        printf("range START STOP -- print a sequence[START, ..., STOP-1]\n");
        printf("range START STOP STEP -- print a sequence[START, START + STEP, START + 2*STEP, ..., STOP-1]\n");
        exit(1);
    } else if (argc == 2) {
        *start = 0;
        *stop = atoi(argv[1]);
        *step = 1;
    } else if (argc == 3) {
        *start = atoi(argv[1]);
        *stop = atoi(argv[2]);
        *step = 1;
    } else if (argc == 4) {
        *start = atoi(argv[1]);
        *stop = atoi(argv[2]);
        *step = atoi(argv[3]);
    } else {
        printf("Error:\nToo many variables");
        exit(2);
    }
}

void range_init(range *seq) {
    seq->iter = seq->start;
}

bool range_run(range *seq) {
    return (seq->step > 0 && seq->iter < seq->stop) ||
           (seq->step < 0 && seq->iter > seq->stop);
}

int range_next(range *seq) {
    return seq->iter += seq->step;
}

int range_get(range *seq) {
    return seq->iter;
}

int main(int argc, char *argv[]) {
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for(range_init(&I); range_run(&I); range_next(&I))
            printf("%d\n", range_get(&I));
    return 0;
}