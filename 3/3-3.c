#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1000

void expand(char s1[], char s2[]);
int typesmatch(char a, char b);
int getline(char s[], int lim);

int main(void)
{
    char line[MAXLINE];
    getline(line, MAXLINE);
    char expanded[MAXLINE];

    expand(line, expanded);

    printf("%s\n", expanded);
    return 0;
}


void expand(char s1[], char s2[])
{
    int len = strlen(s1);
    int i, j;
    i = j = 0;

    if (s1[i] == '-') {
        s2[j++] = '-';
        ++i;
    }

    while (i + 2 < len) {
        if (typesmatch(s1[i], s1[i+2]) && s1[i+1] == '-') {
            int k = (i > 0 && s2[j-1] == s1[i]) ? 1 : 0;
            int cond = s1[i+2] - s1[i];

            for (; k <= cond; ++k) {
                s2[j++] = s1[i] + k;
            }

            i += 2;
        }
        else {
            ++i;
        }
    }

    if (s1[i+1] == '-') {
        s2[j++] = '-';
    }

    s2[j] = '\0';
}


int typesmatch(char a, char b)
{
    return ((islower(a) && islower(b)) || (isupper(a) && isupper(b)) || (isdigit(a) && isdigit(b))) ? 1 : 0;
}


int getline(char s[], int lim)
{
    int c, i;
    
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }

    s[i] = '\0';

    return i;
}
