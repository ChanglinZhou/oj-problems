/*
ID: amble_s1
LANG: C++
TASK: barn1
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

const int MAX = 200;
int cows[MAX], gaps[MAX];

int compare( const void* a, const void* b )
{
    return *static_cast<const int*>(a) - *static_cast<const int*>(b);
}

int minBlockedStalls( int c, int m, int s )
{
    int gap = 0;
    memset(gaps, 0, sizeof(gaps));

    for ( int i = 1; i < c; ++i ) {
        gap = cows[i] - cows[i - 1] - 1;
        ++gaps[gap];
    }

    int min = cows[c - 1] - cows[0] + 1;
    int r = m - 1;
    for ( int j = min - 2; j >= 1; --j ) {
        while (r > 0 && gaps[j] > 0) {
            min -= j;
            --gaps[j];
            --r;
        }
    }

    return min;
}

int main ( ) 
{
    int m, s, c;
    memset(cows, 0, sizeof(cows));

    FILE *fin = fopen("barn1.in", "r");
    FILE *fout = fopen("barn1.out", "w");
    assert( fin != NULL && fout != NULL );

    fscanf( fin, "%d %d %d", &m, &s, &c );

    for ( int i = 0; i < c; ++i ) {
        fscanf( fin, "%d", &cows[i] );
    }
    
    qsort( cows, c, sizeof(int), compare );

    fprintf( fout, "%d\n", minBlockedStalls( c, m, s ) );

    fclose(fin);
    fclose(fout);

    return 0;
}