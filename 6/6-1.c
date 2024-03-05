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
struct key *binsearch(char *, struct key *, int);

/* count C keywords */
int main(void)
{
    char word[MAXWORD];
    struct key *p;

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || word[0] == '#') {
            if ((p = binsearch(word, keytab, NKEYS)) != NULL) {
                p->count++;
            }
        }
    }
    
    for (p = keytab; p < keytab + NKEYS; p++) {
        if (p->count > 0) {
            printf("%4d %s\n", p->count, p->word);
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
struct key *binsearch(char *word, struct key *tab, int n)
{
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
    
    while (low <= high) {
        mid = low + (high-low)/2;
        if ((cond = strcmp(word, mid->word)) < 0) {
            high = mid - 1;
        }
        else if (cond > 0) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }

    return NULL;
}
