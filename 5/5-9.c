#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

#define isleapyear(x) (!(x%4) && (x%100)) || !(x%400)

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main(void)
{
    int month, day;

    month_day(2023, 365, &month, &day);
    printf("%d, %d\n", month, day);
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int leap;
    char *p;

    leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    p = &daytab[leap][1];
    
    while (month-- > 0) {
        day += *p++;
    }

    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int leap;
    char *p;
    leap = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
    p = &daytab[leap][1];

    for (; yearday > *p; p++) {
        yearday -= *p;
    }


    *pmonth = (int)(1 + p - &daytab[leap][1]);
    *pday = yearday;
}