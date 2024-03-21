#include <stdlib.h>

#define MAX_PATH 256

char *getfilename(char *src);
void reverse(char *s);

char *getfilename(char *src)
{
    char *fname = malloc(MAX_PATH * sizeof(char));
    char *fp = fname;
    char *np;

    for (np = src; !(*np == '\n' || *np == '.'); np++) {}
    np--;

    while (*np != '\\') {
        *fp++ = *np--;
    }
    *fp = '\0';

    reverse(fname);
    return fname;
}

void reverse(char *s)
{
    int c;
    char *t = s;

    while (*t) {
        t++;
    }
    t--;

    for (; s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}