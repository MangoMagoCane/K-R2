#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 1000

int getline(char line[], int maxline);


int main(void)
{
    int len = 0;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        printf("%s%d\n", line, len);
    }

    return 0;
}

int getline(char s[], int lim)
{
    int c, i;
    bool stillTrailingWS = true;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ) {
        if (!(c == ' ' || c == '\t')) {
            stillTrailingWS = false;
        }

        if (stillTrailingWS == false) {
            s[i] = c;
            ++i;
        }
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
