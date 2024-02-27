#include <stdio.h>

#define MAXIMUM 100

int main(void)
{
    int c, i;
    int lim = MAXIMUM;
    char s[MAXIMUM];

    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
        s[i] = c;
    }

    // for (i = 0; (i < lim - 1) * ((c = getchar()) != '\n') * (c != EOF); ++i) {
    //     s[i] = c;
    // }

    printf("%s\n", s);

    return 0;
}