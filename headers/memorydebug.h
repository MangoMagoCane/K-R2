#include <stdlib.h>
#include <string.h>

static int __malfree__ = 0;

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);
    __malfree__++;
    return ptr;
}

void my_free(void *ptr)
{
    __malfree__--;
    free(ptr);
}

char *my_strdup(char *s) {
    __malfree__++;
    return strdup(s);
}

#define malloc(x) my_malloc(x)
#define free(x) my_free(x)
#define strdup(x) my_strdup(x)
#define mallocsfreed() printf("Unfreed mallocs: %d\n", __malfree__);
