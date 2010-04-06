/*
ID: amble_s1
LANG: C
TASK: gift1
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAXYEAR 400

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 2


typedef enum t_WeekDay {
    Sunday, Monday, Tuesday, Wednesday,
    Thursday, Friday, Saturday
} WeekDay;

typedef enum t_Month {
    Jan, Feb, Mar, Apr,
    May, Jun, Jul, Aug,
    Sep, Oct, Nov, Dec
} Month;

typedef struct t_DayOn13th
{
    WeekDay day;
    int number;
} DayOn13th;


BOOL IsLeapYear( int year )
{
    return ( (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0) );
}

int DaysInMonth( int year, Month mon )
{
    int days;

    switch(mon) {
        
    }
}
int main () {
    DayOn13th days[7];
    FILE* fin = fopen("friday.in", 'r');
    FILE* fout = fopen("friday.out", 'w');
    int i, j, n, year;
    Month mon;

    for ( i = 0; i < 7; ++i )
    {
        days[i].day = i;
        days[i].number = 0;
    }

    fscanf("%d", &n);
    assert( 0 <= n && n <= MAXYEAR );

    for( i = 1900; i < year + n; ++i )
    {
        for( mon = Jan; mon <= Dec; ++mon )
        {

        }
    }
    return 0;
}
