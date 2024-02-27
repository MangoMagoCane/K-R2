#include <stdio.h>
#include <string.h>

void recursitoa(int, char []);
void reverse(char[], int, int);

int main(void)
{
    char string[100];

    recursitoa(-1234, string);
    printf("%s\n", string);

    char dog[] = "123456";

    reverse(dog, 0, strlen(dog)-1);
    printf("%s\n", dog);
}


void recursitoa(int n, char s[])
{
    static int i = 0;
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10 != 0) {
        recursitoa(n / 10, s);
    }
    s[i++] = n % 10 + '0';
    s[i] = '\0';
}


void reverse(char s[], int i, int len)
{
    int c = s[i];
    s[i] = s[len-i];
    s[len-i] = c;

    if (i < len/2) {
        reverse(s, ++i, len);
    }
}
