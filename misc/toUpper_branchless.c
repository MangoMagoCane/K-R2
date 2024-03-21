#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXCHARS 1000000
#define MAXASCII 128
#define MAXITER 1000

void upper(char *s, int lim);
void upper_branchless(char *s, int lim);
void randomizeChars(char *s, int lim, int maxCode);

int main(void)
{
    char randChars[MAXCHARS]; 
    double regular, branchless;
    clock_t temp, t;

    t = 0;
    for (int i = 0; i < MAXITER; i++) {
        randomizeChars(randChars, MAXCHARS, MAXASCII);
        temp = clock();
        upper(randChars, MAXCHARS);
        t += clock() - temp;
    }
    regular = ((double) t / CLOCKS_PER_SEC);

    t = 0;
    for (int i = 0; i < MAXITER; i++) {
        randomizeChars(randChars, MAXCHARS, MAXASCII);
        temp = clock();
        upper_branchless(randChars, MAXCHARS);
        t += clock() - temp;
    }
    branchless = ((double) t / CLOCKS_PER_SEC);

    // printf("%s\n", randChars);
    printf("branched: %f\nbranchless %f\n", regular, branchless);
}

void upper(char *s, int lim)
{
    for (int i = 0; i < lim; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 0x20;
        }
    }
}

void upper_branchless(char *s, int lim)
{
    for (int i = 0; i < lim; i++) {
        s[i] -= 0x20 * (s[i] >= 'a' && s[i] <= 'z');
    }
}

void randomizeChars(char *s, int lim, int maxCode)
{
    for (int i = 0; i < lim; i++) {
        s[i] = rand() % maxCode;
    }
}