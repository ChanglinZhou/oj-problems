#include <stdio.h>
#include <string.h>

#define MAX 300
unsigned int table[MAX/2 + 2];

unsigned int f( unsigned int n )
{
    memset( table, 0, sizeof(table) );
    
    short i, j;
    table[n/2 + 1] = (n > 0);
    for( i = 1; i <= n/2; ++i )
    {
        table[i] = 1;
        for( j = 1; j <= i/2; ++j )
            table[i] += table[j];

        table[n/2 + 1] += table[i];
    }    

    return table[n/2 + 1];
}

int main()
{
    unsigned int t, n;
    scanf("%d", &t);
    while( t-- )
    {
        scanf("%d", &n);
        printf( "%d\n", f(n) );
    }

    return 0;
}