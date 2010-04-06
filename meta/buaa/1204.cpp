#include <stdio.h>

#define MAX 100

void bubbleSort( int* array, int size )
{
    int i, j, tmp;
    for ( i = 0; i < size; ++i )
        for ( j = size - 1; j > i; --j )
        {
            if (array[j-1] > array[j])
            {
                tmp = array[j-1];
                array[j-1] = array[j];
                array[j] = tmp;
            }
        }
}

int main()
{
    int t, n, m, array[MAX];
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        m = 0;
        for (m = 0; m < n; ++m)
            scanf("%d", array + m);
        bubbleSort(array, n);
        for (m = 0; m < n; ++m)
        {
            printf("%d", array[m]);
            if ( m < n - 1)
                printf(" ");
        }
        printf("\n");
    }

    return 0;
}