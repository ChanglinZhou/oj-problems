#include <stdio.h>

#define MAX 10
int apple[MAX + 1];

int main()
{
    int i, t, h, number;
    scanf("%d", &t);

    while(t--)
    {
        for( i = 0; i < MAX; ++i )
        {
            scanf("%d", apple + i);
        }

        scanf("%d", &h);
        h += 30;
        for( i = 0, number = 0; i < MAX; ++i )
        {
            if( apple[i] <= h )
                ++number;
        }
        printf("%d\n", number);
    }

    return 0;
}