/*
 * Author: meta(carmack.shi@gmail.com)
 * Nail and board
*/

#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX = 100001;

int maxHeight( int coords[], int s, int t, int v )
{
    int height = 0;
    for ( int i = s; i <= t; ++i )
    {
        if ( coords[i] <= v && coords[i] > height )
            height = coords[i];
    }

    return height;
}

void judgeCoordinate( int coords[], int k, int v )
{
    coords[k] = v;
}


int main()
{
    int coords[MAX];
    int n, m;
    int op, k, s, t, v;
    
    memset(coords, 0, sizeof(coords));
    scanf( "%d %d", &n, &m );
    for ( int i = 1; i <= n; ++i )
    {
        scanf("%d", &coords[i]);
    }

    for ( int i = 1; i <= m; ++i )
    {
        scanf("%d", &op);
        if ( op == 0 )
        {
            scanf( "%d %d", &k, &v );
            judgeCoordinate(coords, k, v);
        }
        else // 1
        {
            scanf( "%d %d %d", &s, &t, &v );
            printf("%d\n", maxHeight(coords, s, t, v));
        }
    }


    return 0;
}