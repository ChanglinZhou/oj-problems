#include <stdio.h>
#include <math.h>

unsigned char perfect( int number )
{
    int sum = 1;
    int i, up;
    up = sqrt((double)number);
    for ( i = 2; i <= up; ++i )
        if ( number % i == 0 )
            sum += (i + number / i);

    return sum == number;
}

int main()
{
    int i;
    for ( i = 1; i <= 1000; ++i )
        if ( perfect(i) )
            printf("%d\n", i);

    return 0;
}