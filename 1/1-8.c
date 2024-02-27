#include <stdio.h>

main()
{
    int c;
    int ws = 0;
    char ws_chars[] = {' ', '\n', '\t', '\r', '\v', '\f'};
    

    while ((c = getchar()) != EOF)
        for (int i = 0; i < 6; i++)
            if (c == ws_chars[i])
                ++ws;

    printf("%d\n", ws);
}