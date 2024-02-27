#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINE 1000

int getlinep(char *s, int);
int atoip(char *);
void reversep(char *);
void reversep_recursive(char *s, int i, int len);
int strindexp(char *, char *);

int main(void)
{
    char line[MAXLINE];

    // int len = getlinep(line, MAXLINE);

    // printf("%s %d\n", line, len);
    // reversep(line);
    // printf("%s\n", line);

    printf("%d\n", strindexp("the doggy", "z"));

    return 0;
}


int getlinep(char *s, int lim) 
{
    int c;
    char *t = s;

    while (--lim > 0 && (c=getchar()) != EOF && c != '\n') {
        *t++ = c;
    }
    if (c == '\n') {
        *t++ = c;
    }
    *t = '\0';

    return t - s;
}

int atoip(char *s) 
{
    int n, sign;

    for (; isspace(*s); s++) {}

    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-') {
        s++;
    }

    for (n = 0; isdigit(*s); s++) {
        n = 10 * n + (*s - '0');
    }

    return sign * n;
}


void reversep_recursive(char *s, int i, int len)
{
    int c = *(s+i);
    *(s+i) = *(s+len-i);
    *(s+len-i) = c;

    if (i < len/2) {
        reversep_recursive(s, ++i, len);
    }
}


void reversep(char *s)
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


int strindexp(char *s, char *t)
{
    char *si = s; 
    char *ti = t;
    char *sj; 

    for (; *si != '\0'; si++) {
        for (sj = si; *ti != '\0' && *sj == *ti; ti++, sj++) {}
        if (ti > t && *ti == '\0') {
            return (int)(si - s);
        }
    }

    return -1;
}