#include <stdio.h>

enum errorcodes {
    INVLDARGCNT
};

int match_count = 6;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Error: usage ./a -n\n");
    }

    return 0;
}