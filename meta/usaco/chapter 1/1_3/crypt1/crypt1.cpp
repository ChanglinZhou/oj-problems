/*
ID: amble_s1
LANG: C++
TASK: crypt1
*/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{
    int n, digits[10];
    FILE *fin, *fout;
    fin = fopen( "crypt1.in", "r" );
    fout = fopen( "crypt1.out", "w" );

    assert ( fin != NULL && fout != NULL );

    // read file
    fscanf( fin, "%d", &n );
    for ( int i = 0; i < n; ++i ) {
        fscanf( fin, "%d", &digits[i] );
    }


    return 0;
}