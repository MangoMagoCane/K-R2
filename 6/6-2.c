// TODO: everything, no clue how to approach this problem or what it's even asking

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