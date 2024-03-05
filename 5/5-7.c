#include <stdio.h>
#include <string.h>
#include "../headers/getline.h"

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLENS 100000 /* max length of any input line */

int getline(char *, int);
int readlines(char lines[], char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main(void)
{
    int nlines; /* number of input lines read */
    char lines[MAXLENS];
    char *lineptr[MAXLINES]; /* pointers to text lines */

    if ((nlines = readlines(lines, lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

/* readlines: read input lines */
int readlines(char lines[], char *lineptr[], int maxlines)
{
    int len;
    int nlines = 0;
    char *p = lines;

    while ((len = getline(p, MAXLENS + lines - p)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        } else {
            p[len-1] = '\0'; /* delete newline */
            lineptr[nlines++] = p;
            p += len;
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

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) { /* do nothing if array contains */
        return; /* fewer than two elements */
    }

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}