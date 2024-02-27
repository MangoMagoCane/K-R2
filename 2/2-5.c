#include <stdio.h>
#include <stdbool.h>

int any(char s1[], char s2[]);
void toset(char s[]);

int main(void)
{
    char str1[] = "qqqz";
    char str2[] = "abcdefghijklndz";

    int pos = any(str1, str2);
    printf("%d\n", pos);

    return 0;
}


int any(char s1[], char s2[])
{
    toset(s2);

    for (int i = 0; s1[i] != '\0'; ++i) {
        for (int j = 0; s2[j] != '\0'; ++j) {
            if (s1[i] == s2[j]) {
                return i;
                
            }
        } 
    }

    return -1;
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