#include <stdio.h>

#define MAX 12
int main()
{
    int i, t, me, mum, cost[MAX];

    scanf("%d", &t);
    while( t-- )
    {
        for ( i = 0; i < MAX; ++i )
            scanf("%d", cost + i);

        me = mum = 0;
        for ( i = 0; i < MAX; ++i )
        {
            me += (300 - cost[i]);
            if ( me < 0 )
                break;

            mum += me;
            me %= 100;
            mum -= me;
        }
        if( i == MAX )
            printf("%d\n", 6 * mum / 5 + me);
        else
            printf("-%d\n", i + 1);
    }

    return 0;
}