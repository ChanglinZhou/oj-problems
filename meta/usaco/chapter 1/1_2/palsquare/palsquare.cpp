/*
ID: amble_s1
LANG: C++
TASK: palsquare
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX 300
#define LEN 20

char map[20];
char digits[LEN];
char square_digits[LEN];

bool isPalindromic( char* p )
{
    int length = strlen(p);

    int j = length / 2;
    int i;
    for ( i = 0; i < j; ++i )
        if ( p[i] != p[length - 1 - i] )
            break;

    return (i == j);
}

void convert( int n, int b, char *p )
{
    memset(p, 0, sizeof(char)*LEN);
    int digit;
    int len = 0;

    while ( n ) {
        digit = n % b;
        p[len] = map[digit];
        n /= b;
        ++len;
    }

    for ( int i = 0; i < len / 2; ++i )
    {
        p[i] = p[i] + p[len - 1 - i];
        p[len - 1 - i] = p[i] - p[len - 1 - i];
        p[i] = p[i] - p[len - 1 - i];
    }
}

int main () 
{
    // Initialization
    FILE *fin, *fout;
    for ( int i = 0; i < 10; ++ i )
    {
        map[i] = '0' + i;
        map[10 + i] = 'A' + i;
    }

    // Read input
    fin = fopen("palsquare.in", "r");
    fout = fopen("palsquare.out", "w");
    assert( fin && fout );
    int b;
    fscanf( fin, "%d", &b );

    //
    for ( int j = 1; j <= MAX; ++j )
    {
        convert( j, b, digits);
        convert(j * j, b, square_digits);
        if ( isPalindromic(square_digits) )
            fprintf(fout, "%s %s\n", digits, square_digits);
    }


    fclose(fin);
    fclose(fout);
    return 0;
}