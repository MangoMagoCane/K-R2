#include <stdio.h>
#include "getline.h"

#define MAXLINE 100
#define MAXLINES 100

int main(void)
{
    int len;
    int i = 0;
    char line[MAXLINE];
    char *lines[MAXLINES];

    while ((len = getline(line, MAXLINE)) > 0) {
        lines[i++] = line; 
    }

    for (; i > 0; i--) {
        printf("%s\n", *(*lines)++);
    }


}


