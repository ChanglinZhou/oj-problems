/*
ID: amble_s1
LANG: C
TASK: friday
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef unsigned int BOOL;
#define TRUE 1
#define FALSE 0

BOOL IsLeap( int year )
{
    return ( year%4 == 0 && ( year%100 != 0 || year%400 == 0 ) );
}

int mtab[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int MonthLength(int year, int month)
{
    if( month == 1 ) /*February*/
        return mtab[month] + IsLeap(year);
    else
        return mtab[month];
}

int main()
{
    FILE *fin, *fout;
    /*
    i -- ith day in the week
    y -- year
    m -- month
    dow -- day of week
    n -- the nth year
    */
    int i, y, m, dow, n;
    /*
    total number of each day of the week in 13th of each month (1900 + n - 1)
    */
    int tdow[7];
    fin = fopen("friday.in", "r");
    fout = fopen("friday.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf(fin, "%d", &n);

    memset(tdow, 0, sizeof(tdow));

    /*
    day of week: Jan 13, 1900 was a Saturday = 0
    */
    dow = 0;
    for(y = 1900; y < 1900+n; ++y)
    {
        for(m = 0; m < 12; ++m)
        {
            tdow[dow]++;
            dow = (dow + MonthLength(y, m)) % 7;
        }
    }

    for( i = 0; i < 7; ++i )
    {
        if(i)
            fprintf(fout, " ");
        fprintf(fout, "%d", tdow[i]);
    }
    fprintf(fout, "\n");

    return 0;
}