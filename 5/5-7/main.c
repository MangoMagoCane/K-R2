#include <stdio.h>
#include "sortlines.h"

static char *lineptr[MAXLINES]; /* pointers to text lines */
static char lines[MAXLINES][MAXLEN];

/* sort input lines */
int main(void)
{
    int nlines; /* number of input lines read */

    if ((nlines = readlines(lineptr, lines, MAXLINES)) >= 0) {
        new_qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}
