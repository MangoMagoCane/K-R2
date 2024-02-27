#include <stdio.h>

int lower(int c);
int lowerv2(int c);

int main(void)
{
    printf("%c\n", lower('A'));
    printf("%c\n", lowerv2('a'));
}


int lower(int c)
{
    if (c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
    } 
    else {
       return c;
    }
}


int lowerv2(int c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}