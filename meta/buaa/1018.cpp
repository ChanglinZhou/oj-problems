#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int L = 20000;
const int M = 100;
bool rock[L + 1];
int opt[L + 1];

template<class T>
inline T min( T a, T b )
{
    return (a < b) ? a : b;
}

void getMinRocks( int l, int s, int t )
{
    if ( l < 0 || s < 0 || t < 0 || s > t || l < s )
        return;

    int r, x;
    r = M + 1;
    for ( x = s; x <= t; ++x )
    {
        if ( opt[l - x] >= 0 )
            r = min(r, opt[l - x]);
    }

    if ( r < M + 1 )
        opt[l] = r + rock[l];
}


int main()
{
    int l, pos;
    int s, t, m;

    while ( scanf( "%d", &l ) != EOF )
    {
        if ( l == 0 )
            break;

        scanf( "%d %d %d", &s, &t, &m );
        memset( rock, 0, sizeof(rock) );
        for ( int i = 0; i < m; ++i )
        {
            scanf( "%d", &pos );
            rock[pos] = 1;
        }
        memset( opt, -1, sizeof(opt) );
        opt[0] = 0;
        for ( int i = 0; i <= l; ++i )
            getMinRocks( i, s, t );
        printf( "%d\n", opt[l] );
    }

    return 0;
}