#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "headers/wrlines.h"

#define MAXLINES 5000 /* max #lines to be sorted */

void qsort2(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);
void swap(void *v[], int i, int j);
void reverseptr(void *v[], int len);
int cmpwrapper(char *s1, char *s2);

int numeric, reverse, foldcases, dirorder;

/* sort input lines */
int main(int argc, char *argv[])
{
    char *lineptr[MAXLINES]; /* pointers to text lines */
    int nlines, c;
    numeric = reverse = foldcases = dirorder = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'n':
                    numeric = 1;
                    break;
                case 'r':
                    reverse = 1;
                    break;
                case 'f':
                    foldcases = 1;
                    break;
                case 'd':
                    dirorder = 1;
                    break;
                default:
                    printf("find: illegal option %c\n", c);
                    printf("Usage: sort -n -r -f -d");
                    return -1;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) < 0) {
        printf("input too big to sort\n");
        return 1;
    } 

    qsort2((void**) lineptr, 0, nlines-1, (int (*)(void*,void*))(cmpwrapper));

    if (reverse) {
        reverseptr((void**) lineptr, nlines);
    } 

    writelines(lineptr, nlines);
    return 0;
}

/* qsort2: sort v[left]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;

    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */
        
    swap(v, left, (left + right)/2);
    last = left;
    
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);
    qsort2(v, left, last-1, comp);
    qsort2(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}


int cmpwrapper(char *s1, char *s2)
{
    #define buflen 100

    char buf1[buflen];
    char buf2[buflen];
    strcpy(buf1, s1);
    strcpy(buf2, s2);

    if (foldcases) {
        strlwr(buf1);
        strlwr(buf2);
    }
    if (dirorder) {
        for (int i = 0; s1[i] != '\0'; i++) {
            if (!(isalnum(s1[i]) || isspace(s1[i]))) {
                return 0;
            }
        }
        for (int i = 0; s2[i] != '\0'; i++) {
            if (!(isalnum(s2[i]) || isspace(s2[i]))) {
                return 0;
            }
        }
    }

    return (numeric) ? numcmp(buf1, buf2) : strcmp(buf1, buf2);
}

/* swap: swap the values of i and j in an array */
void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* reverseptr: reverse the order of elements in an array */
void reverseptr(void *v[], int len)
{
    for (int i = 0, j = len-1; i < j; i++, j--) {
        swap(v, i, j);
    }
}