#include <stdio.h>
#include <string.h>

#define MAX 20

int a1[2][MAX + 1];
int a2[2][MAX + 1];
int b1[MAX + 1];

void init()
{
    int i, j;
    for ( i = 0; i <= 1; ++i )
        for ( j = 0; j <= MAX; ++j )
            a2[i][j] = 1;

    for ( i = 0; i <= MAX; ++i )
        b1[i] = 1;
}

int w( int a, int b, int c )
{
    int i, j, k, r, tmp;
    r = 1;
    init();

    if ( a <= 0 || b<= 0 || c <= 0 )
        a = b = c = 0;

    if ( a > MAX || b > MAX || c > MAX )
        a = b = c = MAX;

    for ( i = 1; i <= a; ++i )
    {
        memcpy(a1, a2, sizeof(a1));
        for ( j = 1; j <= b; ++j )
        {
            r = 1;
            for ( k = 1; k <= c; ++k )
            {
                tmp = a2[1][k-1] = r;
                if ( i < j && j < k )
                    r += b1[k-1] - b1[k];
                else
                    r = a1[1][k] + a1[0][k] + a1[1][k-1] - a1[0][k-1];
                a2[0][k-1] = a1[1][k-1];
                a2[0][k] = a1[1][k];
                b1[k-1] = tmp;
            }
            b1[k-1] = a2[1][k-1] = r;
        }
    }

    return r;
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