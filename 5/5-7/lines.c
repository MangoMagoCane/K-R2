#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortlines.h"

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

/* readlines: read input lines */
int readlines(char *lineptr[], char lines[][MAXLEN], int maxlines)
{
    int len, nlines;
    char *p;
    nlines = 0;

    while ((len = getline(lines[nlines], MAXLEN)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        } else {
            lines[nlines][len-1] = '\0'; /* delete newline */
            lineptr[nlines] = lines[nlines];
            nlines++;
        }
    }

    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    while (nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
