#include <stdio.h>

#define MAX 3
int table[MAX] = { 6, 28, 496 };

int main()
{
    int i;
    for ( i = 0; i < MAX; ++i )
        printf("%d\n", table[i]);

    return 0;
}