#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../headers/getchars.h"

enum types {
    COMMENT, STRCONST
};

struct key {
    char *word;
    int count;
} keytab[] = {
    "#define", 0,
    "#include", 0,
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "else", 0,
    "for", 0,
    "if", 0,
    "multi-line comment", 0,
    /* ... */
    "single-line comment", 0,
    "strconst", 0,
    "test_", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
int main(void)
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || word[0] == '#') {
            if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
            printf("%4d %s\n", keytab[n].count, keytab[n].word);
        }
    }
    
    return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch())) {}
    if (c != EOF) {
        *w++ = c;
    }

    if (c == '/') {
        if ((c = getch()) == '/') {
            strcpy(--w, "single-line comment");
        } else if (c == '*'){
            while ((c = getch()) != '*' && c != EOF) {}
            if (c == '*' && (c = getch()) == '/') {
                strcpy(--w, "multi-line comment");
            }
        } else {
            ungetch(c);
        }
        return c;
    }

    if (!(isalpha(c) || c == '#')) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!(isalnum(*w = getch()) || *w == '_')) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';    
    return word[0];
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid - 1;
        }
        else if (cond > 0) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }

    return -1;
}
