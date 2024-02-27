#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 20

double atofv2(char s[]);

int main(void)
{
    char num[MAXLINE] = "12323e-2";

    printf("%f\n", atofv2(num));

    return 0;
}


double atofv2(char s[])
{
    double val, power, sci, num;
    int i, sign, scisign;

    for (i = 0; isspace(s[i]); i++) {
        ;
    }
    
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    if (s[i] == '.') {
        i++;
    }

    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    num = sign * val / power;
    if (!(s[i] == 'e' || s[i] == 'E')) {
        return num;
    }

    scisign = (s[++i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }

    for (sci = 0.0; isdigit(s[i]); i++) {
        sci = 10.0 * sci + (s[i] - '0');
    }

    return (scisign == 1) ? num * pow(10, sci) : num / pow(10, sci);
}