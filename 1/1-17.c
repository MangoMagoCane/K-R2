#include <stdio.h>

#define MAXLINE 1000
#define LINE_MIN 80

int getline(char line[], int maxline);


int main(void)
{
    int len = 0;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len >= LINE_MIN) {
            printf("%s", line);
        }
    }

    return 0;
}

int getline(char s[], int lim)
{
    int c, i;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';

    return i;
}
