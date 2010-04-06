/*
ID: amble_s1
LANG: C++
TASK: namenum
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LEN 13

int main () 
{
    FILE *fin, *fdict, *fout;
    char word[LEN], number[LEN], map[256];
    int nsolutions = 0;

    // Open files
    fin = fopen("namenum.in", "r");
    fdict = fopen("dict.txt", "r");
    fout = fopen("namenum.out", "w");
    assert( fin && fdict && fout );
    
    // Initialize keyboard mappings
    memset( map, 0, sizeof(map) );
    map['A'] = map['B'] = map['C'] = '2';
    map['D'] = map['E'] = map['F'] = '3';
    map['G'] = map['H'] = map['I'] = '4';
    map['J'] = map['K'] = map['L'] = '5';
    map['M'] = map['N'] = map['O'] = '6';
    map['P'] = map['R'] = map['S'] = '7';
    map['T'] = map['U'] = map['V'] = '8';
    map['W'] = map['X'] = map['Y'] = '9';

    // Read number
    fscanf( fin, "%s", number );

    // Read dictionary and do checking
    while ( fscanf( fdict, "%s", word ) != EOF )
    {
        char *p, *q;
        for ( p = word, q = number; *p && *q; ++p, ++q )
        {
            if ( map[*p] != *q )
                break;
        }

        if ( !*p && !*q )
        {
            fprintf( fout, "%s\n", word );
            ++nsolutions;
        }
    }

    if ( nsolutions == 0 )
        fprintf( fout, "NONE\n" );

    // Close files
    fclose(fin);
    fclose(fdict);
    fclose(fout);

    return 0;
}