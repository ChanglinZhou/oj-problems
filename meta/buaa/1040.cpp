#include <stdio.h>

unsigned long long akm( int m, int n )
{
    if( m == 0 ) {
        return n + 1;
    }
    else {
        if( n == 0 )
            return akm( m - 1, 1 );
        else
            return akm( m - 1, akm( m, ( n - 1 ) ) );
    }
}

int main()
{
    int t, m, n;
    scanf("%d", &t);
    while( scanf("%d %d", &m, &n) != EOF )
    {
        printf("%d\n", akm( m, n ));
    }

    return 0;
}