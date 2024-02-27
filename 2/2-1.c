#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <math.h>

int main(void)
{
    printf("char: %d, %d\n", CHAR_MIN, CHAR_MAX);
    printf("schar: %d, %d\n", SCHAR_MIN, SCHAR_MAX);


    printf("short: %d, %d\n", SHRT_MIN, SHRT_MAX);
    printf("ushort: %d, %d\n", 0, USHRT_MAX);


    printf("int: %d, %d\n", INT_MIN, INT_MAX);
    printf("uint: %d, %lu\n", 0, UINT_MAX);

    printf("long: %d, %d\n", LONG_MIN, LONG_MAX);
    printf("ulong: %d, %lu\n", 0, ULONG_MAX);

    printf("\n");

    long max = 0;
    long min = 0;
    int i = 1;

    while (i > 0) {
        i *= 2;
        if (i-1 > max) {
            max = i-1;
        }
    }

    min = i;

    printf("direct computation, long: %d, %d\n", min, max);
}