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

int times[MAX / (sizeof(int)*8)];

void set_times( int start, int end )
{
    int i, j, k;
    for ( k = start; k < end; ++k )
    {
        i = k / (sizeof(int)*8);
        j = k % (sizeof(int)*8);
        times[i] |= (1 << j);
    }
}

int get_times( int index )
{
    int i, j;
    i = index / (sizeof(int)*8);
    j = index % (sizeof(int)*8);

    return ((times[i] >> j) & 0x00000001);
}


int main () 
{
    //
    FILE *fin, *fout;
    int i, n, start, end, min, max;
    memset(times, 0, sizeof(times));
    //
    fin = fopen("milk2.in", "r");
    fout = fopen ("milk2.out", "w");
    assert(fin != NULL && fout != NULL);
    fscanf(fin, "%d", &n);
    i = min = max = 0;
    while ( i < n )
    {
        fscanf(fin, "%d %d", &start, &end);
        if (min > start || min == 0)
            min = start;
        if (max < end || max == 0)
            max = end;
        set_times(start, end);
        ++i;
    }

    //
    int tmp, busy, idle, last, cur;
    tmp = busy = idle = 0;
    last = 1;
    for ( end = start = min; end <= max; ++end )
    {
        cur = get_times(end);
        if ( cur != last )
        {
            tmp = end - start;
            start = end;

            if (!cur)
                busy = (busy < tmp) ? tmp : busy;
            else
                idle = (idle < tmp) ? tmp : idle;
        }
        last = cur;
    }
    tmp = end - start;
    busy = (busy < tmp) ? tmp : busy;

    fprintf(fout, "%d %d\n", busy, idle);
    // close files
    fclose(fin);
    fclose(fout);
    return 0;
}