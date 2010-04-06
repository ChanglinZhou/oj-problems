#include <stdio.h>

#define LEN 50

int recursiveMinimum( int* array, int begin, int end )
{
    if ( begin == end )
        return array[begin];

    int min = recursiveMinimum(array, begin, end - 1);
    if ( min > array[end] )
        min = array[end];

    return min;
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
        
        printf("%d\n", recursiveMinimum(array, 0, n - 1));
    }

    return 0;
}