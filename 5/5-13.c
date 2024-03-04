#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/wrlines.h"

#define MAXLEN 100
#define MAXLINES 100

enum errorcodes {
    SUCCESS, INVLDCMDARG, TOOMANYARGS, NOINPUT
};

int main(int argc, char *argv[])
{
    char *lineptr[MAXLINES];
    int nlines;
    int linesToPrint = 10;

    if (argc == 2) {
        if ((linesToPrint = atoi(argv[1])) >= 0) {
            printf("Error: not a positive unsigned int\n");
            return INVLDCMDARG;
        }
        
        linesToPrint *= -1;
    } else if (argc > 2) {
        printf("Error: too many command-line arguments");
        return TOOMANYARGS;
    }

    if ((nlines = readlines(lineptr, MAXLEN)) < 0) {
        printf("error: no lines inputted");
        return NOINPUT;
    }

    for (int i = nlines-1; i >= 0 && linesToPrint > 0; i--, linesToPrint--) {
        printf("%s\n", lineptr[i]);
    }
    while (--nlines > 0) {
        afree(lineptr[nlines]);
    }

    return SUCCESS;
}
