#include <stdio.h>

int bitcount(unsigned x);
int bitcountv2(unsigned x);

int main(void)
{
    printf("v1: %d\n", bitcount(13));
    printf("v2: %d\n", bitcountv2(15));
}

int bitcount(unsigned x)
{
    int b;
    for (b = 0; x != 0; x >>= 1) {
        if (x & 01) {
            b++;
        }
    }

    return b;
}

int bitcountv2(unsigned x)
{
    int b;
    for (b = 0; x != 0; ++b) {
        x &= x-1;
    }

    return b;
}
// x = 1101
// x &= (x01) == 1101 & 1100 == 1100
// 
// x = 1110
// x &= (x01) == 1110 & 1101 == 1100