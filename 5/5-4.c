#include <stdio.h>
#include <string.h>

int strend(char *s, char *t);

int main(void)
{
    char str1[100] = "the dog is a funny man";
    char str2[100] = "man";
    int res = strend(str1, str2);

    printf("%d\n", res);

    return 0;
}


int strend(char *s, char *t)
{
    int slen = strlen(s);
    int tlen = strlen(t);

    if (tlen > slen) {
        return 0;
    }

    for (s += slen-tlen; *s != '\0'; s++, t++) {
        if (*s != *t) {
            return 0;
        }
    }

    return 1;
}