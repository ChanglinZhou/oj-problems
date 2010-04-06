#include <stdio.h>

typedef unsigned char BOOL;
#define TRUE 1
#define FALSE 0

char line[6000];

char matrix[3000][3000];

BOOL IsSquare( int x, int y, int length, int m, int n )
{
    if ( x + length > m || y + length > n )
        return FALSE;

    int i, j;
    for ( i = 0; i < length; ++i )
        for ( j = 0; j < length; ++j )
        {
            if( matrix[x+i][y+j] == '1' )
                return FALSE;
        }

        return TRUE;
}

int maxLength( int m, int n )
{
    int i, j, maxLength;
    maxLength = 0;

    for ( i = 0; i < m; ++i )
        for ( j = 0; j < n; ++j )
        {
            int length = maxLength;
            while(IsSquare(i, j, ++length, m, n))
                ;
            --length;

            if ( maxLength < length )
                maxLength = length;
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

        int i;
        for( i = 0; i < m; ++i )
        {
            gets( line );
            short* src = (short*)line;
            char* des = (char*)(matrix + i);
            while (*des++ = (char)*src++)
                ;
        }

        printf( "%d\n", maxLength( m, n ) );
    }

    return 0;
}