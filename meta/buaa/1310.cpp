#include <stdio.h>
#include <string.h>

#define MAX 1000
char bitmap[MAX + 1];

int main()
{
    int i, j, t, n, data;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(bitmap, 0, sizeof(bitmap));

        for( i = n; i >= 1; --i )
        {
            scanf("%d", &data);
            n -= (bitmap[data] > 0);
            bitmap[data] = 1;
        }

        printf("%d\n", n);
        
        for( i = 1, j = 0; i <= MAX; ++i )
        {
            if( bitmap[i] )
            {
                ++j;
                printf("%d", i);
                if( j == n )
                    printf("\n");
                else
                    printf(" ");
            }
        }
    }

    return 0;
}