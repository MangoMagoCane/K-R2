#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/memorydebug.h"

#define HASHSIZE 101

typedef struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
} nlist;

unsigned hash(char *s);
nlist *lookup(char *s);
nlist *install(char *name, char *defn);
nlist *undef(char *name);

static nlist *hashtab[HASHSIZE]; /* pointer table */

int main(void)
{
    install("dog", "cat");
    install("doggy", "kitty");
    install("foo", "bar");
    install("elephant", "ostrich");
    undef("elephant");

    nlist *np, *np_buf;
    for (int i = 0; i < HASHSIZE; i++) {
        if (hashtab[i] != NULL) {
            np = hashtab[i];
            while (np != NULL) {
                np_buf = np->next;
                printf("%s: %s\n", np->name, np->defn);
                free(np->name);
                free(np->defn);
                free(np);
                np = np_buf;
            }
        }
    }

    mallocsfreed();
    return 0;
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np; /* found */
        }
    }
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
nlist *install(char *name, char *defn)
{
    nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else {
        free((void *) np->defn);
    }

    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}

nlist *undef(char *name)
{
    nlist *np;
    nlist *prev_np = NULL;
    unsigned hashval = hash(name);

    for (np = hashtab[hashval]; np != NULL; prev_np = np, np = np->next) {
        if (strcmp(name, np->name) != 0) {
            continue;
        }
        if (prev_np != NULL) {
            prev_np->next = np->next;
        } else {
            hashtab[hashval] = np->next;
        }
        free(np->name);
        free(np->defn);
        free(np);
        break;
    }
}