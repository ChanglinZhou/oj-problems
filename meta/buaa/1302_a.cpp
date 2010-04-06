#include <stdio.h>

#define MAX 20

int result[MAX + 1][MAX + 1][MAX + 1];

void init()
{
    int i, j, k;
    i = 0;
    for ( j = 0; j <= MAX; ++j )
        for ( k = 0; k <= MAX; ++k )
            result[i][j][k] = 1;
    j = 0;
    for ( i = 0; i <= MAX; ++i )
        for ( k = 0; k <= MAX; ++k )
            result[i][j][k] = 1;
    k = 0;
    for ( i = 0; i <= MAX; ++i )
        for ( j = 0; j <= MAX; ++j )
            result[i][j][k] = 1;
}

int w( int a, int b, int c )
{
    int i, j, k;
    init();
    if ( a <= 0 || b<= 0 || c <= 0 )
        a = b = c = 0;
    if ( a > MAX || b > MAX || c > MAX )
        a = b = c = MAX;
    for ( i = 1; i <= a; ++i )
        for ( j = 1; j <= b; ++j )
            for ( k = 1; k <= c; ++k )
            {
                if ( i < j && j < k )
                    result[i][j][k] = result[i][j][k-1] + result[i][j-1][k-1] - result[i][j-1][k];
                else
                    result[i][j][k] = result[i-1][j][k] + result[i-1][j-1][k] + result[i-1][j][k-1] - result[i-1][j-1][k-1];
            }
            return result[a][b][c];
}

int main()
{
    int t, a, b, c;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d %d", &a, &b, &c);
        printf("%d\n", w(a, b, c));
    }
    return 0;
}