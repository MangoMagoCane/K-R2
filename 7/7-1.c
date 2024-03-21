#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../headers/filename.h"

enum options { DEFAULT, LOWER, UPPER };

int main(int argc, char *argv[])
{   
    int c;
    int option;
    char *fname = getfilename(argv[0]);

    if (strcmp(fname, "lower") == 0) {
        option = LOWER;
    } else if (strcmp(fname, "upper") == 0) {
        option = UPPER;
    } else {
        option = DEFAULT;
    }

    while ((c = getchar()) != EOF) {
        switch (option) {
        case LOWER:
            c = tolower(c);
            break;
        case UPPER:
            c = toupper(c);
            break;
        }
        putchar(c);
    }

    free(fname);
    return 0;
}
