#include <stdio.h>
#include <stdbool.h>

#define NL_CHARS 6

int main(void)
{
    int c, prev_c;
    int chars_per_line = 0;
    char ws_chars[NL_CHARS] = {' ', '\n', '\t', '\r', '\v', '\f'};
    bool place_char = true;

    while ((c = getchar()) != EOF) {
        ++chars_per_line;

        if (c == '\n') {
            chars_per_line = 0;
        }
    
        if (chars_per_line == 0) {
            putchar(c);
        } else {
            for (int i = 0; i < NL_CHARS; i++) {
                if ((c == ws_chars[i]) && (c == prev_c)) {
                    place_char = false;
                    break;
                }
            }

            if (place_char) {
                putchar(c);
            }
            
            place_char = true;
        }
        
        prev_c = c;
    }

    return 0;
}