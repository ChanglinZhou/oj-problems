#include <stdio.h>

#define LEN 100

void insertionSort( int* array, int size )
{
    int i, j, tmp;

    for ( i = 1; i < size; ++ i )
    {
        tmp = array[i];
        for ( j = i - 1; j >= 0 && tmp < array[j]; --j )
            array[j + 1] = array[j];
        array[j + 1] = tmp;
    }
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

        insertionSort(array, n);

        for (i = 0; i < n; ++i)
        {
            if ( i > 0 )
                printf(" ");
            printf("%d", array[i]);
        }
        printf("\n");
    }

    return 0;
}