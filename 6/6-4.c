#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../headers/getchars.h"
#include "../headers/memorydebug.h"

#define MAXWORD 100

typedef struct WordCount {
    char *word;
    int count;
} WordCount;

typedef struct Treenode {
    WordCount *wcp;
    struct Treenode *left;
    struct Treenode *right;
} Treenode;

Treenode *addtree(Treenode *p, char *word);
void treefree(Treenode *p);
char *my_strdup(char *s);
void addnodetoarray(Treenode *p, WordCount *words[], int *ip);
void my_qsort(WordCount *v[], int left, int right);
void my_swap(WordCount *v[], int i, int j);

void *my_malloc(size_t size);
void my_free(void *ptr);

int unique_words = 0;

int main(void)
{
    Treenode *root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    printf("%d\n", unique_words);

    WordCount *words[unique_words];
    int index = 0;
    addnodetoarray(root, words, &index);
    my_qsort(words, 0, index-1); /* index ends up representing len */

    for (int i = 0; i < index; i++) {
        printf("%s %d\n", words[i]->word, words[i]->count);
    }

    treefree(root);
    mallocsfreed();
    return 0;   
}

Treenode *addtree(Treenode *p, char *word)
{
    int cond;

    if (p == NULL) {
        unique_words++;
        p = (Treenode *) malloc(sizeof(Treenode)); 
        p->left = p->right = NULL;
        p->wcp = (WordCount *) malloc(sizeof(WordCount)); 
        p->wcp->count = 1;
        p->wcp->word = my_strdup(word);
    } else if ((cond = strcmp(word, p->wcp->word)) < 0) {
        p->left = addtree(p->left, word);
    } else if (cond > 0) {
        p->right = addtree(p->right, word);
    } else {
        p->wcp->count++;
    }

    return p;
}

void addnodetoarray(Treenode *p, WordCount *words[], int *ip)
{
    if (p != NULL) {
        words[*ip] = p->wcp;
        (*ip)++;
        addnodetoarray(p->left, words, ip);
        addnodetoarray(p->right, words, ip);
    }
}

void treefree(Treenode *p) 
{
    if (p != NULL) {
        treefree(p->left);
        treefree(p->right);
        // printf("%s: %d\n", p->wcp->word, p->wcp->count);
        free(p->wcp->word);
        free(p->wcp);
        free(p);
    }
}

char *my_strdup(char *s)
{
    char *p = (char *) malloc(strlen(s)+1); 
    if (p != NULL) { 
        strcpy(p, s);
    }

    return p;
}

/* my_qsort: sort v[left]...v[right] into increasing order */
void my_qsort(WordCount *v[], int left, int right)
{
    int i, last;

    if (left >= right) {
        return;
    }
    my_swap(v, left, (left + right)/2);
    last = left;

    for (i = left+1; i <= right; i++) {
        if (v[i]->count < v[left]->count) {
            my_swap(v, ++last, i);
        }
    }
    
    my_swap(v, left, last);
    my_qsort(v, left, last-1);
    my_qsort(v, last+1, right);
}

/* my_swap: interchange v[i] and v[j] */
void my_swap(WordCount *v[], int i, int j)
{
    WordCount *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

