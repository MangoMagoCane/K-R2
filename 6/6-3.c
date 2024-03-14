#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../headers/getchars.h"

#define MAXWORD 100

typedef struct countnode {
    int linenum;
    struct countnode *next;
} countnode;

typedef struct treenode {
    char *word;
    countnode *count;
    struct treenode *left;
    struct treenode *right;
} treenode;

typedef struct noisenode {
    char *word;
    struct noisenode *left;
    struct noisenode *right;
} noisenode;

treenode *addtree(treenode *, char *, int);
void treeprint(treenode *);
treenode *talloc(void);
char *strdupkr(char *);
void appendcount(treenode *count, int num);
int getwordnl(char *word, int lim);
noisenode *addnoiseword(noisenode *p, char *word);
void noisefree(noisenode *p, int printwords);
int isnoiseword(char *word, noisenode *p);
void printcountnode(countnode *p);

char *noisewords[] = {
    "the", "a", "an", "and", "but", "for", "so", "yet"
};

int main(void)
{
    treenode *root = NULL;
    char word[MAXWORD];
    int linenum = 1;

    noisenode *nwroot = NULL;
    int nwlen = sizeof(noisewords) / sizeof(noisewords[0]);
    for (int i = 0; i < nwlen; i++) {
        nwroot = addnoiseword(nwroot, noisewords[i]);
    }

    while (getwordnl(word, MAXWORD) != EOF) {
        if (word[0] == '\n') {
            linenum++;
        }
        if (isalpha(word[0]) && isnoiseword(word, nwroot) == 0) {
            root = addtree(root, word, linenum);
        }
    }

    treeprint(root);
    printf("Total line number: %d\n", linenum);
    noisefree(nwroot, 0);
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

/* strdupkr: make a duplicate of s */
char *strdupkr(char *s) 
{
    char *p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p != NULL) {
        strcpy(p, s);
    }

    return p;
}

/* appendcount: prepend num to linkedlist in treenode p */
void appendcount(treenode *p, int num) 
{
    if (p->count != NULL && p->count->linenum == num) {
        return;
    }
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

        printcountnode(p->count);
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

/* addnoiseword: add a node with w, at or below p */
noisenode *addnoiseword(noisenode *p, char *w) 
{
    int cond;

    if (p == NULL) {
        p = (noisenode *) malloc(sizeof(noisenode));
        p->word = strdupkr(w);
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) < 0) {
        p->left = addnoiseword(p->left, w);
    } else if (cond > 0) {
        p->right = addnoiseword(p->right, w);
    }

    return p;
}

/* noisefree: free p with printwords flag */
void noisefree(noisenode *p, int printwords) 
{
    if (p != NULL) {
        noisefree(p->left, printwords);
        if (printwords) {
            printf("%s\n", p->word);
        }
        noisefree(p->right, printwords);
        free(p);
    }
}

/* isnoiseword: check if word is found in noisenode binary tree p */
int isnoiseword(char *word, noisenode *p)
{
    int retval = 1;
    if (p == NULL) {
        return 0;
    } 

    int cond = strcmp(word, p->word);
    if (cond < 0) {
        retval = isnoiseword(word, p->left);
    } else if (cond > 0) {
        retval = isnoiseword(word, p->right);
    }

    return retval;
}

/* printcountnode: print and free countnod linkedlist p */
void printcountnode(countnode *p) 
{
    if (p == NULL) {
        return;
    }

    printcountnode(p->next);
    printf("%i ", p->linenum);
    free(p);
}