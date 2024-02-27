#include <stdio.h>

int FahrToCelc(int fahr);

int main(void) 
{
    int celcius = FahrToCelc(20);
    printf("%d\n", celcius);

    return 0;
}


int FahrToCelc(int fahr)
{
    int celc = 5 * (fahr-32) / 9;
    return celc;
}