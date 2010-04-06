/*
ID: amble_s1
LANG: C++
TASK: transform
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX 11

bool isTransform1( const char square1[][MAX], const char square2[][MAX], int n )
{
    int i, j;
    for ( i = 0; i < n; ++i )
    {
        for ( j = 0; j < n; ++j )
        {
            if ( square1[i][j] != square2[j][n - 1 - i] )
                break;
        }
        if ( j < n )
            break;
    }

    return ( i >= n );
}


bool isTransform2( const char square1[][MAX], const char square2[][MAX], int n )
{
    int i, j;
    for ( i = 0; i < n; ++i )
    {
        for ( j = 0; j < n; ++j )
        {
            if ( square1[i][j] != square2[n - 1 - i][n - 1 - j] )
                break;
        }
        if ( j < n )
            break;
    }

    return ( i >= n );
}

bool isTransform3( const char square1[][MAX], const char square2[][MAX], int n )
{
    int i, j;
    for ( i = 0; i < n; ++i )
    {
        for ( j = 0; j < n; ++j )
        {
            if ( square1[i][j] != square2[n - 1 - j][i] )
                break;
        }
        if ( j < n )
            break;
    }

    return ( i >= n );
}

bool isTransform4( const char square1[][MAX], const char square2[][MAX], int n )
{
    int i, j, r;
    r = (n - 1) / 2;
    for ( j = 0; j <= r; ++j )
    {
        for ( i = 0; i < n; ++i )
        {
            if ( square1[i][j] != square2[i][n - 1 - j] )
                break;
        }
        if ( i < n )
            break;
    }

    return ( j > r );
}

bool isTransform5( const char square1[][MAX], const char square2[][MAX], int n )
{
    char square[MAX][MAX];
    int i, j, r;
    for ( i = 0; i < n; ++i )
        for ( j = 0; j < n; ++j )
            square[i][n - 1 - j] = square1[i][j];

    if ( isTransform1( square, square2, n ) )
        return true;

    if ( isTransform2( square, square2, n ) )
        return true;

    if ( isTransform3( square, square2, n ) )
        return true;
    
    return false;
}

bool isTransform6( const char square1[][MAX], const char square2[][MAX], int n )
{
    int i, j;
    for ( i = 0; i < n; ++i )
    {
        for ( j = 0; j < n; ++j )
        {
            if ( square1[i][j] != square2[i][j] )
                break;
        }
        if ( j < n )
            break;
    }

    return ( i >= n );
}

int getTransform( char square1[][MAX], char square2[][MAX], int n )
{
    if ( isTransform1( square1, square2, n ) )
        return 1;

    if ( isTransform2( square1, square2, n ) )
        return 2;

    if ( isTransform3( square1, square2, n ) )
        return 3;

    if ( isTransform4( square1, square2, n ) )
        return 4;

    if ( isTransform5( square1, square2, n ) )
        return 5;

    if ( isTransform6( square1, square2, n ) )
        return 6;

    return 7;
}
int main () 
{
    // Initialization
    FILE *fin, *fout;
    char square1[MAX][MAX], square2[MAX][MAX];
    memset( square1, 0, sizeof(square1) );
    memset( square2, 0, sizeof(square2) );

    // Read input
    fin = fopen("transform.in", "r");
    fout = fopen("transform.out", "w");
    assert( fin && fout );
    int i, n;
    fscanf( fin, "%d", &n );
    for ( i = 0; i < n; ++i )
    {
        fscanf( fin, "%s", square1[i] );
    }
    for ( i = 0; i < n; ++i )
    {
        fscanf( fin, "%s", square2[i] );
    }
    
    fprintf( fout, "%d\n", getTransform( square1, square2, n ) );

    fclose(fin);
    fclose(fout);
    return 0;
}