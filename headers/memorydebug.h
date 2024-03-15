#include <stdlib.h>

static int malfree = 0;

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);
    malfree++;
    return ptr;
}

void my_free(void *ptr)
{
    malfree--;
    free(ptr);
}

#define malloc(x) my_malloc(x)
#define free(x) my_free(x)
#define mallocsfreed() printf("Unfreed mallocs: %d\n", malfree);
