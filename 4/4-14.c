#include <stdio.h>

#define swap(t,x,y) {t temp = x; x = y; y = temp;}

int main(void)
{
    int one = 1;
    int two = 2;

    swap(int, one, two);
    printf("%d, %d", one, two);
    
    return 0;
}

