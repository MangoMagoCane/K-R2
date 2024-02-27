#include <stdio.h>

#define LEN 10

int binsearch(int x, int v[], int n);
int binsearchv2(int x, int v[], int n);

int main(void)
{
    int array[LEN];
    for (int i = 0; i < LEN; ++i) {
        array[i] = i + 1;
    }

    printf("1: %d\n", binsearch(3, array, LEN));
    printf("2: %d\n", binsearchv2(3, array, LEN));
}


int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;

        if (x < v[mid]) {
            high = mid + 1;
        }
        else if (x > v[mid]) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }

    return -1; 
}


int binsearchv2(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (low + high) / 2;
        if (x <= v[mid]) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }

    return (x == v[low]) ? low : -1;
}
