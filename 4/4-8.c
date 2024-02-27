#include <stdio.h>

char buf = EOF;

int getch(void);
void ungetch(int);


int getch(void) 
{
    char retval;

    if (buf != EOF) {
        retval = buf;
        buf = EOF;
    } else {
        retval = getchar();
    }

    return retval;
}


void ungetch(int c)
{
    buf = c;
}
