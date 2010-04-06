#include <stdio.h>

unsigned long long f( int n )
{
    if( n < 0 )
        return 0;

    if( n == 0 )
        return 1;

    unsigned long long f0 = 1;
    unsigned long long f1 = f0;
    unsigned long long f2 = f1;

    int i;
    for( i = 2; i <= n; ++i )
    {
        f2 = f1 + f0;
        f0 = f1;
        f1= f2;
    }


    return f2;
}

int main()
{
    int t, n;
    scanf("%d", &t);
    while( scanf("%d", &n) != EOF )
    {
        printf("%d\n", f(n));
    }

    return 0;
}