#include <stdio.h>
#include <string.h>

#define MIN( a, b ) \
    (a) < (b) ? (a) : (b)

#define MAX( a, b ) \
    (a) > (b) ? (a) : (b)

#define INDEX( i, j ) \
    (( (3000 + 3000 - (i) + 1) * (i) ) / 2 + ((j) - (i)))

char line[6000];
short s[3000];
short f[3001*1500];

void processInput( )
{
    short* des = (short*)line;
    char value;
    short* p = s;
    while ( value = (char)*des++ )
    {
        if ( p == s )
            *p = value - '0';
        else
            *p = *(p-1) + value - '0';
        ++p;
    }
}


int maxSquareLength( int m, int n )  
{
    memset( f, 0, sizeof(f) );
    int r, i, j, length, max;
    max = 0;
    for ( r = 0; r < m; ++r )
    {
        gets(line);
        processInput();
        for( i = 0; i < n; ++i )
            for( j = i; j < n; ++j )
            {
                if ( i == 0 )
                {
                    if ( s[j] == 0 )
                        f[INDEX(i,j)] += 1;
                    else
                        f[INDEX(i,j)] = 0;
                }
                else
                {
                    if ( s[i-1] == s[j] )
                        f[INDEX(i,j)] += 1;
                    else
                        f[INDEX(i,j)] = 0;
                }
                length = MIN( j-i+1, f[INDEX(i,j)] );
                max = MAX(max, length);
            }
    }

    return max;
}

int main()
{
    int m, n;

    while ( scanf("%d %d\n", &m, &n) != EOF )
    {
        if ( m == 0 || n == 0 )
            break;

        printf( "%d\n", maxSquareLength( m, n ) );
    }
    return 0;
}