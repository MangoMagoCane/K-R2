#include <stdio.h>
#include <string.h>
#include "../headers/filename.h"

#define MAXLINE 1000

typedef struct FileStruct {
    FILE *fp;
    char line[MAXLINE];
} FileStruct;

enum errcodes { ARG_COUNT=0, FREAD_1, FREAD_2 };

char *rstrip(char *s);

int main(int argc, char *argv[])
{
    FileStruct fsp1, fsp2;
    char *fname = getfilename(argv[0]);
    char *frp1, *frp2;
    int linenum = 1;

    if (argc != 3) {
        fprintf(stderr, "Usage: ./%s file file", fname);
        exit(ARG_COUNT);
    }
    if ((fsp1.fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: Can't open %s\n", fname, argv[1]);
        exit(FREAD_1);
    }
    if ((fsp2.fp = fopen(argv[2], "r")) == NULL) {
        fprintf(stderr, "%s: Can't open %s\n", fname, argv[2]);
        exit(FREAD_2);
    }

    while (1) {
        linenum++;
        frp1 = fgets(fsp1.line, MAXLINE, fsp1.fp);
        frp2 = fgets(fsp2.line, MAXLINE, fsp2.fp);
        rstrip(fsp1.line);
        rstrip(fsp2.line);

        if (strcmp(fsp1.line, fsp2.line) != 0) {
            printf("first difference on line: %d\n", linenum);
            printf("%s: %s\n", argv[1], (frp1 != NULL) ? fsp1.line : "EOF");
            printf("%s: %s\n", argv[2], (frp2 != NULL) ? fsp2.line : "EOF");
            exit(0);
        }

        if (frp1 == NULL && frp2 == NULL) {
            break;
        }
    }

    printf("files match");
    exit(0);
}

char *rstrip(char *s)
{
    char *sp = s;
    while (*sp++) {}
    sp--;
    while (sp != s && (*sp == ' ' || *sp == '\n' || *sp == '\0')) {
        sp--;
    }
    *++sp = '\0';
    return s;
}