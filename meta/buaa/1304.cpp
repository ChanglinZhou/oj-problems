#include <stdio.h>
#include <string.h>

int f( int n )
{
    int a, b, c, d, i;
    a = b = c = d = 1;
    for( i = 2; i <= n; ++i )
    {
        a = a + c;
        d = b + d;
        a = a + b;
        b = a - b;
        a = a - b;
        d = d + c;
        c = d - c;
        d = d - c;
        if( a >= 7654321 && b >= 7654321 && c >= 7654321 && d >= 7654321 )
        {
            a %= 7654321;
            b %= 7654321;
            c %= 7654321;
            d %= 7654321;
        }
    }
    return a;
}

int main()
{
    int t, n;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        printf("%d\n", f(n));
    }
    return 0;
}