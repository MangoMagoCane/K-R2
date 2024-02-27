#include <stdio.h>

#define SPACES_PER_TAB 8

int getline(char line[], int linemax);

int main(void)
{
    int c;
    int ts_index = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < SPACES_PER_TAB - ts_index; ++i) {
                putchar(' ');
            }

            ts_index = 0;
            continue;
        }

        putchar(c);
        ts_index++;

        if (c == '\n') {
            ts_index = 0;    
        }
    }
    
    return 0;
}
