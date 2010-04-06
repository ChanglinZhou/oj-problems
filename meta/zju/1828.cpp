#include <stdio.h>
#include <string.h>

#define M 5000
#define N 112
#define UNIT 1000000000 /*10-bits dec number*/
typedef unsigned int uint32;
uint32 table[M + 1][N];

void zeroFill(uint32* p)
{
    memset(p, 0, sizeof(uint32) * N);
}

void printFibonacci(uint32* p)
{
    if (p == NULL)
        return;
    
    int i = 0;
    while (p[i] == 0 && i < N)
    	++i;
    if (i == N)
    	printf("0");
    
    int j = i;
    while (j < N)
    {
    	if (j == i)
            printf("%d", p[j]);
        else
            printf("%09d", p[j]);
        ++j;
    }
    printf("\n");
}

void BigNumber_Add(uint32* p1, uint32* p2, uint32* p)
{
    if (p1 == NULL || p2 == NULL || p == NULL)
        return;

    int i = N - 1;
    unsigned char carry = 0;
    uint32 sum;

    while (i >=0 && (p1[i] || p2[i]))
    {
    	sum = p1[i] + p2[i] + carry;
    	carry = sum / UNIT;
        p[i] = sum % UNIT;
        i--;
    }
    if (i >= 0)
    	p[i] = carry;
}

uint32* DP_Fibonacci(int n)
{     
    int i;
    for (i = 2; i <= n; i++)
    {
    	BigNumber_Add(table[i - 1], table[i - 2], table[i]);
    }
    return table[n];
}

int main()
{
    int i, n;
    for (i = 0; i <= M;++i)
    {
        zeroFill(table[i]);
    }

    table[1][N - 1] = 1;
    
    while (scanf("%d", &n) != EOF) {
        printFibonacci(DP_Fibonacci(n));
    }
    
    return 0;
}
