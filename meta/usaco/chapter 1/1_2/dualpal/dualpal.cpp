/*
ID: amble_s1
LANG: C++
TASK: dualpal
*/
#include <stdio.h>
#include <assert.h>

const int minBase = 2;
const int maxBase = 10;

char digits[33];

bool IsPalindromic( int num, int base )
{
    if ( num < 0 || base > maxBase || base < minBase )
        return false;

    int n = 0;
    while (num > 0) {
        digits[n] = num % base;
        num /= base;
        ++n;
    }

    int i = 0;
    while ( i < n / 2 ) {
        if (digits[i] != digits[n - 1 - i])
            break;
        ++i;
    }

    return i == n / 2;
}

bool IsDualPalindromic( int num )
{
    int c = 0;
    for ( int b = minBase; b <= maxBase; ++b ) {
        if ( IsPalindromic(num, b) )
            ++c;
    }

    return c >= 2;
}

int main( )
{
    FILE *fin, *fout;
    int n, s;

    
    
    fin = fopen( "dualpal.in", "r" );
    fout = fopen( "dualpal.out", "w" );
    assert( fin != NULL && fout != NULL );

    fscanf( fin, "%d %d", &n, &s );

    for ( int i = 0; i < n; ++i ) {
        while ( !IsDualPalindromic(++s) );
        fprintf( fout, "%d\n", s );
    }

    fclose(fin);
    fclose(fout);
    return 0;
}