#include <stdio.h>

#define LEN 100

void swap(int *a, int *b)
{
    if ( a == b )
        return;

    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
void selectionSort(int *array, int size)
{
    if ( size == 1 )
        return;

    int i, min;
    min = 0;
    for ( i = 1; i < size; ++i )
    {
        if ( array[min] > array[i] )
            min = i;
    }
    swap(array, array + min);

    selectionSort(array + 1, size - 1);
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

        selectionSort(array, n);

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