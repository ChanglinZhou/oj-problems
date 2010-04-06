#include <stdio.h>

#define MAX 15
int table[MAX + 1] = { 0, 2, 4, 11, 31, 83, 227, 616, 1674, 4550, 12367, 33617, 91380, 248397, 675214, 1835421 };

int main()
{
    int t, k;
    scanf("%d", &t);
    while( t-- )
    {
        scanf("%d", &k);
        printf("%d\n", table[k]);
    }
    return 0;
}