#include <stdio.h>

void printLine( int n, int m )
{
    int j;
    for ( j = (n - m) / 2; j >= 1; --j )
        printf("-");
    for ( j = 1; j <= m; ++j )
        printf("*");
    for ( j = (n - m) / 2; j >= 1; --j )
        printf("-");
    printf("\n");
}

void printAll( int n )
{
    int i;
    for ( i = 1; i <= n; i += 2 )
        printLine(n, i);
    for ( i = n - 2; i >= 1; i -= 2 )
        printLine(n, i);
}

int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printAll(n);
    }
    return 0;
}