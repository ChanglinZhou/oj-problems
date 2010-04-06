/*
ID: amble_s1
LANG: C++
TASK: calfflac
*/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int MAXSTR = 20000;
const int MAXPAL = 2000;
const int MAXLINE = 80;

char fulltext[MAXSTR + 1];
char text[MAXSTR + 1];

char *pal = NULL;
int pallen = 0;

void findPalindrome( )
{
    char *p, *fwd, *bkwd;
    int len;

    for ( p = text; *p; ++p ) {
        // center
        for( bkwd = fwd = p; 
             bkwd >= text && *fwd && *fwd == *bkwd;
             ++fwd, --bkwd );

        ++bkwd;
        len = fwd - bkwd;
        if ( len > pallen ) {
            pal = bkwd;
            pallen = len;
        }

        // left-middle
        for ( bkwd = p, fwd = p + 1;
              bkwd >= text && *fwd && *fwd == * bkwd;
              ++fwd, --bkwd );

        ++bkwd;
        len = fwd - bkwd;
        if ( len > pallen ) {
            pal = bkwd;
            pallen = len;
        }
    }
}

int main()
{
    FILE *fin, *fout;
    fin = fopen("calfflac.in", "r");
    fout = fopen("calfflac.out", "w");
    assert( fin && fout );

    char c;
    char *p, *q;
    int i, j, n;

    p = fulltext;
    q = text;
    while ( (c = getc(fin)) != EOF ) {
        if (isalpha(c))
            *q++ = tolower(c);
        *p++ = c;
    }
    *p = '\0';
    *q = '\0';

    findPalindrome();

    fprintf( fout, "%d\n", pallen );

    n = pal - text + 1;
    for ( i = 0, p = fulltext; *p; ++p ) {
        if (isalpha(*p))
            ++i;

        if (i == n)
            break;
    }

    for( j = 0; j < pallen && *p; p++ ) {
        fputc(*p, fout);
        if(isalpha(*p))
            ++j;
    }

    fprintf(fout, "\n");


    fclose(fin);
    fclose(fout);

    return 0;
}

