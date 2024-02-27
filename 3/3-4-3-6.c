#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAXLINE 50

void itoa(int n, char s[]);
void itoapad(int n, char s[], int pad);
void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void)
{
    int num = INT_MIN;
    char char_num[MAXLINE];

    itoa(num, char_num);
    printf("itoa: %s\n", char_num);

    itob(num, char_num, 16);
    printf("itob: %s\n", char_num);

    itoapad(num, char_num, 14);
    printf("itoapad: %s\n", char_num);

    return 0;
}


void itoa(int n, char s[])
{
    int i, sign;
    sign = (n < 0) ? -1 : 1;
    i = 0;

    do {
        s[i++] = sign * (n % 10) + '0';
    } while ((n /= 10) != 0); 

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}


void itob(int n, char s[], int b)
{
    int i, sign, c;
    sign = (n < 0) ? -1 : 1;
    i = 0;

    if (b > 36 || b < 2) {
        strcpy(s, "invalid base");
        return;
    }

    do {
        c = sign * (n % b);
        s[i++] = (c <= 9) ? (c + '0') : (c-10 + 'A');
    } while ((n /= b) != 0);

    if (sign < 0) {
        s[i++] = '-';
    }

    s[i] = '\0';
    reverse(s);
}


void itoapad(int n, char s[], int pad)
{
    int i, sign;
    sign = (n < 0) ? -1 : 1;
    i = 0;

    do {
        s[i++] = sign * (n % 10) + '0';
    } while ((n /= 10) != 0); 

    if (sign < 0) {
        s[i++] = '-';
    }

    for (; i < pad; ++i) {
        s[i] = '_';
    }

    s[i] = '\0';
    reverse(s);
}


void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }   
}