#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_PATH 256

void getfilename(char *name);
void reverse(char *s);

enum options { DEFAULT, LOWER, UPPER };

static char file_name[MAX_PATH];

int main(int argc, char *argv[])
{   
    int c;
    int option;

    getfilename(argv[0]);
    if (strcmp(file_name, "lower") == 0) {
        option = LOWER;
    } else if (strcmp(file_name, "upper") == 0) {
        option = UPPER;
    } else {
        option = DEFAULT;
    }

    while ((c = getchar()) != EOF) {
        switch (option) {
        case LOWER:
            c = tolower(c);
            break;
        case UPPER:
            c = toupper(c);
            break;
        }
        putchar(c);
    }
}

void getfilename(char *name)
{
    char *np;
    char *fp = file_name;

    for (np = name; !(*np == '\n' || *np == '.'); np++) {}
    np--;

    while (*np != '\\') {
        *fp++ = *np--;
    }
    reverse(file_name);
}

void reverse(char *s)
{
    int c;
    char *t = s;

    while (*t) {
        t++;
    }
    t--;

    for (; s < t; s++, t--) {
        c = *s;
        *s = *t;
        *t = c;
    }
}