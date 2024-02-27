#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

extern int _CRT_glob = 0; // disables MinGW globbing that is added to this program. Source: https://willus.org/mingw/_globbing.shtml

#define MAXOP 100 /* max size of operand or operator */ 
#define MAXVAL 100 /* maximum depth of val stack */
enum types {
    NUMBER, VARIABLE 
};

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
int linep; 

void push(double);
double pop(void);
int getop(char []);

int main(int argc, char *argv[])
{
    int type;
    double op2;
    char *s;     

    while (--argc > 0) {
        s = *++argv;
        switch (getop(s)) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0) {
                    push(pop() / op2);
                } else {
                    printf("error: zero divisor\n");
                }
                break;
        }
    }

    printf("%.8g\n", pop());
    return 0;
}

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i = 0;

    if (!isdigit(s[i]) && s[i] != '.') {
        return s[i]; /* not a number */
    }

    if (isdigit(s[i])) {
        while (isdigit(s[++i])) {}
    }
    if (s[i] == '.') {
        while (isdigit(s[++i])) {}
    }
    
    if (!isdigit(s[i]) && s[i] != '.') {
        return '\0';
    }

    s[i] = '\0';
    return NUMBER;
}