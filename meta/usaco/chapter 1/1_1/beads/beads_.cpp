/*
ID: amble_s1
LANG: C
TASK: beads
*/
#include <stdio.h>

#define MAX 350

char beads[MAX+1];


int length


int main () 
{
    FILE *fin, *fout;
    int i, n, len, max;

    fin = fopen("beads.in", "r");
    fout = fopen ("beads.out", "w");
    assert(fin != NULL && fout != NULL);

    fscanf("%d %s", &n, beads);
    
    max = 0;
    for( i = 1; i <= n; ++i )
    {

    }

    // close files
    fclose(fin);
    fclose(fout);
    return 0;
}