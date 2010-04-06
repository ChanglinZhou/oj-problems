#include <stdio.h>
#include <string.h>

#define MAX 100000000
#define LENGTH 2500

unsigned int plants[LENGTH + 1];

unsigned int calculate(int x, int y, int z, int n)
{
    unsigned int seeds, i, j;
    seeds = 1;
    memset(plants, 0, sizeof(plants));

    for( i = 1; i <= n; ++i )
    {
        plants[0] = seeds;
        seeds = 0;

        unsigned int m = ( i >= z - 1 ) ? z - 1 : i;

        for( j = m; j >= 1; --j )
        {
            plants[j] = plants[j-1];
            if( x <= j && j <= y ) 
            {
                seeds += plants[j];
                if ( seeds >= MAX )
                    seeds %= MAX;
            }
        }
    }

    unsigned int total = 0;

    for( i = 1; i <= z - 1; ++ i )
    {
        total += plants[i]; 
        if (total >= MAX)
            total %= MAX;
    }

    return total;
}

int main()
{
    int x, y, z, n;

    while( scanf("%d %d %d %d", &x, &y, &z, &n) != EOF )
    {
        if( x == 0 && y == 0 && z == 0 && n == 0 )
            break;
        printf("%d\n", calculate(x, y, z, n));
    }
    return 0;
}
