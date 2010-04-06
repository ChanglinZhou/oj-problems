# include <stdio.h>
# include <string.h>

#define LIMIT 3000

char line[2*LIMIT];
short up[LIMIT+1], left[LIMIT+1], square[LIMIT+1];

int maxLength( int m, int n )
{
    int i, j, maxLength;
    maxLength = 0;

    memset( up, 0, LIMIT + 1 );
    memset( square, 0, LIMIT + 1 );
    left[0] = 0;
    for ( i = 1; i <= m; ++i )
    {
        gets( line );
        short* p = (short*)line;
        short tmp1, tmp2;
        tmp1 = square[0];
        for ( j = 1; j <= n; ++j )
        {
            if ( (char)(p[j-1]) == '1' )
                up[j] = left[j] = square[j] = 0;
            else
            {
                ++up[j];
                left[j] = left[j-1] + 1;
                tmp2 = square[j];
                square[j] = tmp1 + 1;
                tmp1 = tmp2;

                if ( square[j] > left[j] )
                    square[j] = left[j];
                if ( square[j] > up[j] )
                    square[j] = up[j];

                if ( maxLength < square[j] )
                    maxLength = square[j];
            }
        }
    }
    return maxLength;
}

int main()
{
    int m, n;
    while ( scanf("%d %d\n", &m, &n) != EOF )
    {
        if ( m == 0 || n == 0 )
            break;
        printf( "%d\n", maxLength( m, n ) );
    }
    return 0;
}