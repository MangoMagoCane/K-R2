#include <stdio.h>
#include <stdbool.h>

#define MAXLINE 1000
#define SPACES_PER_TAB 8

int getline(char line[], int maxline);

int main(void)
{
    char line[MAXLINE];
    char entab[MAXLINE];

    bool put_tab = false;
    int len = getline(line, MAXLINE);
    int column_pos = 0;
    int entab_pos = 0;

    for (int i = 0; i < len; ++i) {
        if (i % SPACES_PER_TAB == 0) {
            column_pos = 0;
        } else {
            column_pos++;
        }

        if (line[i] != ' ') {
            put_tab = false;
        } else {
            for (int j = 0; j < SPACES_PER_TAB-column_pos; j++) {
                if (line[i+j] != ' ') {
                    put_tab = false;
                    break;
                }
            }
        }

        if (put_tab) {
            entab[entab_pos++] = '\t';
            i += SPACES_PER_TAB - column_pos;
        } else {
            entab[entab_pos++] = line[i];
        }
        
        put_tab = true;
    }

    entab[entab_pos] = '\0';
    printf("%s", entab);

    return 0;
}


int getline(char s[], int lim)
{
    int c, i;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}