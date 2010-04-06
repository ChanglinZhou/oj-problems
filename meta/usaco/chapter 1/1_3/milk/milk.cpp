/*
ID: amble_s1
LANG: C++
TASK: milk
*/
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

const int M = 5000;

typedef struct farmer {
    int price;
    int amount;
} farmer;

int compare( const void* a, const void* b )
{
    return static_cast<const farmer*>(a)->price - static_cast<const farmer*>(b)->price;
}

int minPrice( farmer* farm, int m, int n )
{
    qsort( farm, m, sizeof(farmer), compare );

    int amount = 0;
    int totalPrice = 0;
    for ( int i = 0; i < n; ++i ) {
        if (n == 0)
            break;
        
        amount = n > farm[i].amount ? farm[i].amount : n;
        totalPrice += farm[i].price * amount;
        n -= amount;
    }

    return totalPrice;
}

int main ( ) 
{
    farmer farm[M];
    FILE *fin = fopen("milk.in", "r");
    FILE *fout = fopen("milk.out", "w");
    assert( fin != NULL && fout != NULL );

    int n, m;
    fscanf( fin, "%d %d", &n, &m );
    for ( int i = 0; i < m; ++i ) {
        fscanf( fin, "%d %d", &farm[i].price, &farm[i].amount );
    }

    fprintf( fout, "%d\n", minPrice( farm, m, n ) );

    fclose(fin);
    fclose(fout);

    return 0;
}