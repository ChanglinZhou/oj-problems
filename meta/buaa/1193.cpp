#include <stdio.h>
#include <math.h>

unsigned char IsPrime( unsigned int number )
{
    if ( number == 1 )
        return 0;

    if ( number == 2 )
        return 1;

    if ( number % 2 == 0 )
        return 0;

    int i, up;
    up = sqrt((double)number);
    for ( i = 3; i <= up; i += 2 )
        if ( number % i == 0 )
            return 0;
    return 1;
}

int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", IsPrime(n));
    }
    return 0;
}
