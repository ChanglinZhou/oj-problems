/*
 * Author: meta(carmack.shi@gmail.com)
 * Ranking range problem
*/

#include <iostream>
#include <cstdlib>
using namespace std;

const int MAX = 100001;

int table[MAX];

int minRange( int ranking[], int n, int a )
{
    memset(table, 0, sizeof(table));

    int sum = 0;
    for ( int i = 1; i <= n; ++i )
    {
        sum += ranking[i];
        table[i] = sum;
    }

    int min = MAX;
    for ( int i = 0; i < n; ++i )
        for ( int j = i + 1; j <= n; ++j )
        {
            if( table[j] - table[i] >= a )
                if ( (j - i - 1) < min )
                    min = j - i - 1;
        }

    return min;
}

int main()
{
    int ranking[MAX];
    int n, a;
    
    memset(ranking, 0, sizeof(ranking));
    scanf( "%d", &n );
    for ( int i = 1; i <= n; ++i )
    {
        scanf("%d", &ranking[i]);
    }
    scanf("%d", &a);

    printf("%d\n", minRange(ranking, n, a));

    return 0;
}