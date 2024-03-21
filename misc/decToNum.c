// Take a decimal number and convert it onto a Roman numeral
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Numeral {
    int dec;
    char *rom;
} Numeral;

Numeral numerals[] = {
    1, "I", 
    4, "IV", 
    5, "V", 
    9, "IX",
    10, "X", 
    40, "XL", 
    50, "L", 
    90, "XC",
    100, "C", 
    400, "CD", 
    500, "D", 
    900, "CM",
    1000, "M"
};

#define NELEMENTS (sizeof(numerals) / sizeof(numerals[0]))

void numeralify(char *numeral, int number, Numeral *numarr);

int main(int argc, char *argv[])
{
    char numeral[16];
    int number = 7;
    // if (!(argc == 2 && ((number = strtol(argv[1], 0x0, 10)) > 0) && number < 4000)) {
    //     printf("Usage: ./numeral n");
    //     return 1;
    // }
    for (int i = 1; i < 4000; i++) {
        numeralify(numeral, i, numerals);
        printf("%d: %s\n", i, numeral);
    }

    return 0;
}

void numeralify(char *numeral, int number, Numeral *numarr)
{
    char *np = numeral;
    char *rp;
    int i;
    
    while (number > 0) {
        i = NELEMENTS-1;
        while (i >= 0) {
            if (number >= numarr[i].dec) {
                number -= numarr[i].dec;
                rp = numarr[i].rom;
                strcpy(np, rp);
                while (*rp++) {
                    np++;
                }
            } else {
                i--;
            }
        }
    }
    *np = '\0';
}