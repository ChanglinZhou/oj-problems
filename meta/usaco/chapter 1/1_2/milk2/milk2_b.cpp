/*
ID: amble_s1
LANG: C
TASK: milk2
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX 1000000

#define N 5000

int times[MAX + 1];

void set_times( int start, int end )
{
    int k;
    for ( k = start; k < end; ++k )
        times[k] = 1;
}


int main () 
{
    //
    FILE *fin, *fout;
    int i, n, start, end;
    memset(times, 0, sizeof(times));
    //
    fin = fopen("milk2.in", "r");
    fout = fopen ("milk2.out", "w");
    assert(fin != NULL && fout != NULL);
    fscanf(fin, "%d", &n);
    
    for ( i = 0; i < n; ++i )
    {
        fscanf(fin, "%d %d", &start, &end);
        set_times(start, end);
    }

    //
    int tmp, busy, idle, last;
    tmp = busy = idle = 0;
    last = 0;
    for ( end = start = 0; end <= MAX; ++end )
    {
        if ( times[end] != last )
        {
            tmp = end - start;

            if (!times[end])
                busy = (busy < tmp) ? tmp : busy;
            else
                idle = (idle < tmp && start) ? tmp : idle;

            start = end;
        }
        last = times[end];
    }

    fprintf(fout, "%d %d\n", busy, idle);
    // close files
    fclose(fin);
    fclose(fout);
    return 0;
}