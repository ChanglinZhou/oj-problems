#include <stdio.h>

#define LEN 50

void printArray( int* array, int begin, int end )
{
    if ( begin == end )
    {
        printf("%d", array[begin]);
        return;
    }

    printArray(array, begin, end - 1);
    printf(" %d", array[end]);

}

int main()
{
    int i, t, n;
    int array[LEN];
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d", &n);
        for (i = 0; i < n; ++i)
            scanf("%d", array + i);
        
        printArray(array, 0, n - 1);
        printf("\n");
    }

    return 0;
}