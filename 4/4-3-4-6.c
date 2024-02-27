#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100 /* max size of operand or operator */ 
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100
#define VARCOUNT 26
enum types {
    NUMBER, FUNCTION, VARIABLE 
};

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */
bool nlcase = true;

void push(double);
double pop(void);
int getop(char []);
int getch(void);
void ungetch(int);
double dofunction(char []);

struct var {
    double value;
    bool used;
};

/* reverse Polish calculator */
int main(void)
{
    int type, lasttype, currvar;
    double op1, op2, mostrecent;
    char s[MAXOP];

    struct var vars[VARCOUNT];
    for (int i = 0; i < VARCOUNT; i++) {
        vars[i].value = 0.0;
        vars[i].used = false;
    }

    while ((type = getop(s)) != EOF) {
        switch (type) { 
            case NUMBER:
                push(atof(s));
                break;
            case FUNCTION:
                push(dofunction(s));
                break;
            case VARIABLE:
                currvar = s[0] - 'a';
                if (vars[currvar].used) {
                    push(vars[currvar].value);
                }
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
            case '%':
                op2 = pop();
                push((int)pop() % (int)op2);
                break;
            case '?': // show top element
                if (sp > 0) {
                    printf("the top element is: %.8g\n", val[sp-1]);
                } else {
                    printf("no elements in stack\n");
                }
                nlcase = false;
                break;
            case '&': // duplicate top element
                op1 = pop();
                push(op1);
                push(op1);
                break;
            case '~': // swap top two elements
                op2 = pop();
                op1 = pop();
                push(op2);
                push(op1);
                break;
            case '$': // clear stack
                sp = 0;
                nlcase = false;
                printf("stack cleared\n");
                break;
            case '=': // assign variable
                if (lasttype == VARIABLE) {
                    if (vars[currvar].used) {
                        pop();
                    }
                    vars[currvar].value = mostrecent;
                    vars[currvar].used = true;
                    nlcase = false;
                }
                break;
            case '\n':
                if (nlcase) {
                    op1 = pop();
                    printf("\t%.8g\n", op1);
                    mostrecent = op1;
                } else {
                    nlcase = true;
                }
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
        }

        lasttype = type;
    }

    return 0;
}

double dofunction(char s[])
{
    double x, y;
    
    if (strcmp(s, "sin") == 0) {
        return sin(pop());
    }
    if (strcmp(s, "exp") == 0) {
        return exp(pop());
    }
    if (strcmp(s, "pow") == 0) {
        y = pop();
        x = pop();
        if (x == 0 || y <= 0 || (x < 0 && !isdigit(y))) {
            printf("error: pow boundry violation\n");
            nlcase = false;
            return 0.0;
        }
        return pow(x, y);
    }
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
    int c, next, retval;
    int i = 0;

    while ((s[0] = c = getch()) == ' ' || c == '\t') {}
    s[1] = '\0';

    if (!isalnum(c) && c != '.' && c != '-') {
        return c; /* not a number */
    }

    if (isalpha(c)) {
        while (isalpha(s[++i] = c = getch())) {}
        retval = (i > 1) ? FUNCTION : VARIABLE;
    } else {
        /* collect sign */
        if (c == '-') {
            next = getch();
            if (!isdigit(next) && next != '.') {
                ungetch(next);
                return '-';
            }
            s[++i] = c = next;
        }
        /* collect integer part */
        if (isdigit(c)) {
            while (isdigit(s[++i] = c = getch())) {}
        }
        /* collect fraction part */
        if (c == '.') {
            while (isdigit(s[++i] = c = getch())) {}
        }
        retval = NUMBER;
    }

    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

    return retval;
}


int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}


void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE) {
        printf("ungetch: too many characters\n");
    } else {
        buf[bufp++] = c;
    }
}
