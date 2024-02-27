// broken don't bother

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define BUFSIZE 100
#define SIZE 5

int getint(int *pn);
int getch(void);
void ungetch(int);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

int main(void)
{
    int n;
    int array[SIZE];

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++) {}

    for (int i = 0; i < n; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, d, sign;
    bool only_sign = true;
    while (isspace(c = getch())) {}/* skip white space */
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c); /* it is not a number */
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        d = getch();
    }

    if (!isdigit(d)) {
        ungetch(d);
        ungetch(c);
        return 0;
    } 

    c = d;
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
        only_sign = false;
    }

    *pn *= sign;
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}

/* get a (possibly pushed-back) character */
int getch(void) 
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
    else
    buf[bufp++] = c;
}