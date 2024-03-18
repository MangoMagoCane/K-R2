#include <stdlib.h>
#include <string.h>

static int mallocs = 0;
static int frees = 0;

void *my_malloc(size_t size)
{
    void *ptr = malloc(size);
    mallocs++;
    return ptr;
}

void my_free(void *ptr)
{
    frees--;
    free(ptr);
}

char *my_strdup(char *s) {
    mallocs++;
    return strdup(s);
}

#define malloc(x) my_malloc(x)
#define free(x) my_free(x)
#define strdup(x) my_strdup(x)

#define mallocs() printf("mallocs: %d\n", mallocs);
#define frees() printf("frees: %d\n", frees);
#define mallocsfreed() printf("Unfreed mallocs: %d\n", mallocs - frees);
