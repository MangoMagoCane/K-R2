#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char string[]);
void copy(char to[], char from[]);

int main(void)
{
    int len = 0;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s\n", line);
    }

    return 0;
}

int getline(char s[], int lim)
{
    int c, i;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    s[i] = '\0';

    return i;
}

void reverse(char s[])
{
    int len = 1;
    while (s[len] != '\0') {
        ++len;
    }

    char buffer[len];
    copy(buffer, s);

    for (int i = 0; i < len; ++i) {
        s[len-i-1] = buffer[i];
    }
    s[len] = '\0';  
}

void copy(char to[], char from[])
{
    int i = 0;

    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}