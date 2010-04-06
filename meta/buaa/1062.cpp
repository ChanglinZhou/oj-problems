#include <stdio.h>
#include <string.h>

#define MAX 100

unsigned int table[MAX + 1];

unsigned int h( unsigned int n )
{
    memset(table, 0, sizeof(table));
    table[2] = 1;

    int i, j;
    for( i = 3; i <= n; ++i )
        for( j = 2; j <= i - 1; ++j )
            table[i] += table[j] * table[i + 1 - j];

    return table[n];

}

int main()
{
    unsigned int n;
    while( scanf("%d", &n) != EOF )
    {
        printf( "%d\n", h(n) );
    }

    return 0;
}