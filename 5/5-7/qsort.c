#include <string.h>
#include "sortlines.h"

/* new_qsort: sort v[left]...v[right] into increasing order */
void new_qsort(char *v[], int left, int right)
{
    int i, last;
    if (left >= right) { /* do nothing if array contains */
        return; /* fewer than two elements */
    }

    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    new_qsort(v, left, last-1);
    new_qsort(v, last+1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}