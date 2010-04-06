#include <stdio.h>
#include <string.h>

#define MAX 20

int primes[2 * MAX];
int used[MAX];
int ring[MAX];

void getPrimes()
{
    primes[0] = primes[1] = 0;

    int i, j;
    for ( i = 2; i < 2 * MAX; ++i )
        primes[i] = 1;

    for ( i = 2; i < MAX; ++i )
        for ( j = i * i; j < 2 * MAX; j += i )
            primes[j] = 0;
}

void prime_ring( int n, int m )
{
    int i, j;

    if ( n < 0 )
        return;

    if ( n == 0 && primes[ring[1] + ring[m]])
    {
        for ( j = 1; j < m; ++j )
            printf("%d ", ring[j]);
        printf("%d\n", ring[j]);
        return;
    }

    if ( n == m )
    {
        memset(used, 0, sizeof(used));
        memset(ring, 0, sizeof(ring));
        used[1] = 1;
        ring[1] = 1;
        --n;
    }

    for ( i = 2; i <= m; ++i )
    {
        if (!used[i])
            if (primes[ring[m-n] + i])
            {
                used[i] = 1;
                ring[m - n + 1] = i;
                prime_ring(n - 1, m);
                used[i] = 0;
                ring[m - n + 1] = 0;
            }
    }
}

int main()
{
    int n;
    int count = 0;
    getPrimes();
    while ( scanf("%d", &n) != EOF )
    {
        printf("Case %d:\n", ++count);
        if ( n % 2 == 0 )
            prime_ring(n, n);
        printf("\n");
    }

    return 0;
}
