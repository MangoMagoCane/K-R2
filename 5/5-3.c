#include <stdio.h>

void strcatp(char *s, char *t);

int main(void)
{
    char str[100] = "the dog is ";
    char ing[100] = "a funny man";
    
    strcatp(str, ing);
    printf("%s\n", str);

    return 0;
}


void strcatp(char *s, char *t)
{
    while (*s) {
        s++;
    }
    while (*s++ = *t++) {}
}


// void strcat(char s[], char t[])
// {
//     int i, j;
//     i = j = 0;
//     while (s[i] != '\0') {
//         i++;
//     }
//     while ((s[i++] = t[j++]) != '\0') {}
// }