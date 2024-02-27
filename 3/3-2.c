#include <stdio.h>

#define MAXLINE 1000

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int getline(char s[], int lim);


int main(void)
{
    char line[MAXLINE] = "d\nog\t";
    // getline(line, MAXLINE);
    char escaped[MAXLINE];
    char unescaped[MAXLINE];

    printf("%s\n", line);

    escape(escaped, line);
    printf("%s\n", escaped);

    unescape(unescaped, escaped);
    printf("%s\n", unescaped);
}


void escape(char s[], char t[])
{
    int i, j;
    for (i = j = 0; t[i] != '\0'; ++i) {
        switch (t[i]) {
            case '\n': 
                s[j++] = '\\';
                s[j] = 'n';
                break;
            case '\t': 
                s[j++] = '\\';
                s[j] = 't';
                break;
            default:
                s[j] = t[i];
                break;
        }

        ++j;
    }

    s[j] = '\0';
}


void unescape(char s[], char t[])
{
    int i, j;
    for (i = j = 0; t[i] != '\0'; ++i) {
        switch (t[i]) {
            case '\\':
                switch (t[i+1]) {
                    case 'n':
                        s[j] = '\n';
                        break;
                    case 't':
                        s[j] = '\t';
                        break;
                    }
                break;
            default:
                s[j] = t[i];
                break;
        }

        ++j;
    }
    
    s[j] = '\0';
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