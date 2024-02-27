#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE]; 
int bufp = 0; 

int getch(void);
void ungetch(int);
void ungets(char []);


int getch(void) 
{
    char retval;
    
    if (bufp > 0) {
        if ((retval = buf[--bufp]) == EOF) {
            retval = buf[--bufp];
        }
    } else {
        retval = getchar();
    }

    return retval;
}


void ungetch(int c) 
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else if (c != EOF){
            buf[bufp++] = c;
    }
}


void ungets(char s[])
{
    for (int i = strlen(s); i >= 0; i--) {
        ungetch(s[i]);
    }
}
