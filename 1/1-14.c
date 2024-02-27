#include <stdio.h>

#define CHAR_COUNT 94

int main(void) 
{
    int c;
    int char_freq[CHAR_COUNT];

    for (int i = 0; i < CHAR_COUNT; ++i) {
        char_freq[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c >= ' ' && c <= '~') {
            char_freq[c - ' '] += 1;
        }   
    }

    for (int i = 0; i < CHAR_COUNT; ++i) {
        if (char_freq[i] > 0) {
            printf("\"%c\" |", i + ' ');

            for (int j = 0; j < char_freq[i]; ++j) {
                printf("*");
            }
            printf("\n");
        }
    }

    return 0;
}