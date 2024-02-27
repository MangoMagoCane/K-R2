#include <stdio.h>
#include <string.h>

#define MAXLINE 100

int getline(char s[], int lim);
int htoi(char hex[]);

int main(void)
{
    char hex_str[MAXLINE];
    getline(hex_str, MAXLINE);

    printf("%s: %d\n", hex_str, htoi(hex_str));

    return 0;
}

int htoi(char hex[])
{
    int i, n;
    i = n = 0;
    if (hex[0] == '0' && (hex[1] == 'X' || hex[1] == 'x')) {
        i = 2;
    }

    while (1) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            n = (16 * n) + (hex[i] - '0');
        } 
        else if (hex[i] >= 'a' && hex[i] <= 'f') {
            n = (16 * n) + (hex[i] - 'a' + 10);
        }
        else if (hex[i] >= 'A' && hex[i] <= 'F') {
            n = (16 * n) + (hex[i] - 'A' + 10);
        } 
        else {
            return n;
        }

        ++i;
    }
    
    return 0;
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