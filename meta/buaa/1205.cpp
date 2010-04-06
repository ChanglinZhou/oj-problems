#include <stdio.h>

#define MAX 999

int tags[ MAX + 1];

void generatePrimes()
{
    int i, j;
    tags[0] = tags[1] = 0;
    for ( i = 2; i <= MAX; ++i )
        tags[i] = 1;

    for ( i = 2; i <= MAX / 2; ++i )
        if ( tags[i] )
            for ( j = 2*i; j <= MAX; j += i )
                if ( tags[j] )
                    tags[j] = 0;
}

int main()
{
    generatePrimes();
    int i;
    for (i = 2; i <= MAX; ++i )
        if ( tags[i] )
            printf("%d\n", i);

    return 0;
}