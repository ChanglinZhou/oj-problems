#include <stdio.h>

#define LEN 50

int linearSearch( int* array, int size, int key )
{
    if (size == 0)
        return -1;

    if (array[size] == key)
        return size;

    return linearSearch(array, size - 1, key);
}

int main()
{
    int i, t, n, m;
    int array[LEN + 1];

    scanf("%d", &t);

    while (t--) {
        scanf("%d %d", &n, &m);
        for ( i = 1; i <= n; ++i )
        {
            scanf("%d", array + i);
        }
        printf("%d\n", linearSearch(array, n, m));
    }

    return 0;
}

