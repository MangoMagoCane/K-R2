#include <stdio.h>

#define STRLEN 100

void strncpy2(char *, char *, int);
void strncat2(char *, char *, int);
int strncmp2(char *, char *, int);

int main(void)
{
    char one[STRLEN] = "11111";
    char two[STRLEN] = "22222";

    strncpy2(one, two, 3);
    printf("%s\n", one);

    // int res = strncmp2(one, two, 2);
    // printf("%d\n", res);

    return 0;
}


void strncpy2(char *s, char *t, int n)
{
    for (; n > 0 && *t; n--) {
        *s++ = *t++;
    }
    *s = '\0';
}


void strncat2(char *s, char *t, int n)
{
    while (*s) {
        s++;
    }
    for (; n > 0; n++) {
        *s++ = *t++;
    }
}


int strncmp2(char *s, char *t, int n)
{
    while (*s == *t && *s) {
        s++;
        t++;
        n--;
    }
    if (n == 0 || *s == *t) {
        return 0;
    }

    return *s - *t;
}