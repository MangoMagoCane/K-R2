#include <stdio.h>
#include <ctype.h>
#include "calc.h"


/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i = 0;
    int retval;
    static int c = ' ';

    while (c == ' ' || c == '\t') {
        c = getch();
    }
    
    s[0] = c;
    s[1] = '\0';
    
    if (!isdigit(c) && c != '.') {
        retval = c;
        c = ' ';
        return retval; 
    }

    if (isdigit(c)) {
        while (isdigit(s[++i] = c = getch())) {}
    }
    
    if (c == '.')  {
        while (isdigit(s[++i] = c = getch())) {}
    }
    
    s[i] = '\0';

    return NUMBER;
}
