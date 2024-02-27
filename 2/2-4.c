#include <stdio.h>
#include <stdbool.h>

void squeeze(char s1[], char s2[]);
void toset(char s[]);

int main(void)
{
    char str1[] = "abzq";
    char str2[] = "abcdefghijklndz";

    squeeze(str1, str2);
    printf("%s %s\n", str1, str2);

    return 0;
}


void squeeze(char s1[], char s2[])
{
    toset(s2);

    int i, j, k;
    bool in_set = false;

    for (i = j = 0; s1[i] != '\0'; ++i) {
        for (k = 0; s2[k] != '\0'; ++k) {
            if (s2[k] == s1[i]) {
                in_set = true;
                break;
            }
        }
        
        if (!in_set) {
            s1[j++] = s1[i];
        }

        in_set = false;
    }

    s1[j] = '\0';
}


void toset(char s[])
{
    bool in_set = false;
    int i, j;

    for (i = j = 0; s[i] != '\0'; ++i) {
        for (int k = 0; k < j; ++k) {
            if (s[k] == s[i]) {
                in_set = true;
            }
        }

        if (!in_set) {
            s[j++] = s[i];
        }

        in_set = false;
    }

    s[j] = '\0';
}