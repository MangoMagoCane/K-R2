#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../headers/getchars.h"

#define MAXWORD 100

struct tnode {
    char *word;
    int *count;
    struct tnode *left;
    struct tnode *right;
};

char *noise_words[] = {
    "the", "and"
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
struct tnode *talloc(void);
char *strdupkr(char *);
int *alloccount(int *, int); 
int getwordnl(char *word, int lim);

int main(void)
{
    int linenum;
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;

    while (getwordnl(word, MAXWORD) != EOF) {
        if (word[0] == '\n') {
            linenum++;
        }
        if (isalpha(word[0])) {
            root = addtree(root, word, linenum);
        }
    }
    treeprint(root);

    return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
    int cond;

    if (p == NULL) { /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdupkr(w);
        p->count = (int *) malloc(sizeof(int));
        p->count[0] = linenum;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count = alloccount(p->count, linenum);
    } else if (cond < 0) {/* less than into left subtree */
        p->left = addtree(p->left, w, linenum);
    } else {/* greater than into right subtree */
        p->right = addtree(p->right, w, linenum);
    }

    return p;
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* make a duplicate of s */
char *strdupkr(char *s) 
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL) {
        strcpy(p, s);
    }
    return p;
}

int *alloccount(int *count, int num) 
{
    int *p;
    p = (int *) malloc(sizeof(count) + sizeof(int));

    int len = sizeof(p) / sizeof(int) - 1;
    for (int i = 0; i < len; i++) {
        p[i] = count[i];
    }
    p[len] = num;

    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
        // printf("%4d %s\n", p->count, p->word);
        int len = sizeof(p->count) / sizeof(p->count[0]) - 1;
        for (int i = 0; i < len; i++) {
            printf("%d ", p->count[i]);
        }

        printf("%s\n", p->word);
        treeprint(p->right);
    }
}

/* getword: get next word or character from input */
int getwordnl(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
  
    while (isspace(c = getch()) && c != '\n') {}
    if (c != EOF) {
        *w++ = c;
    }
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }

    *w = '\0';
    return word[0];
}