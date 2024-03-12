#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../headers/getchars.h"

#define MAXWORD 100

typedef struct cnode {
    int linenum;
    struct cnode *next;
} countnode;

typedef struct tnode {
    char *word;
    countnode *count;
    struct tnode *left;
    struct tnode *right;
} treenode;

char *noise_words[] = {
    "the", "and"
};

treenode *addtree(treenode *, char *, int);
void treeprint(treenode *);
treenode *talloc(void);
char *strdupkr(char *);
void appendcount(treenode *count, int num);
int getwordnl(char *word, int lim);

int main(void)
{
    treenode *root = NULL;
    char word[MAXWORD];
    int linenum = 1;

    while (getwordnl(word, MAXWORD) != EOF) {
        if (word[0] == '\n') {
            linenum++;
        }
        if (isalpha(word[0])) {
            root = addtree(root, word, linenum);
        }
    }

    treeprint(root);
    printf("Total line number: %d\n", linenum);
    return 0;
}

/* addtree: add a node with w, at or below p */
treenode *addtree(treenode *p, char *w, int linenum)
{
    int cond;

    if (p == NULL) { /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdupkr(w);
        p->count = NULL;
        appendcount(p, linenum);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        appendcount(p, linenum);
    } else if (cond < 0) {/* less than into left subtree */
        p->left = addtree(p->left, w, linenum);
    } else {/* greater than into right subtree */
        p->right = addtree(p->right, w, linenum);
    }

    return p;
}

/* talloc: make a tnode */
treenode *talloc(void)
{
    return (treenode *) malloc(sizeof(treenode));
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

void appendcount(treenode *p, int num) 
{
    countnode *buf = malloc(sizeof(countnode));
    
    buf->linenum = num;
    buf->next = (p->count == NULL) ? NULL : p->count;
    p->count = buf;
}

/* treeprint: in-order print of tree p */
void treeprint(treenode *p)
{
    if (p != NULL) {
        treeprint(p->left);

        printf("%s: ", p->word);
        countnode *ptr = p->count;
        while (ptr != NULL) {
            printf("%i ", ptr->linenum);
            countnode *tempfree = ptr;
            ptr = ptr->next;
            free(tempfree);
        }
        printf("\n");

        treeprint(p->right);
        free(p);
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