#include <stdio.h>

#define WEEKLEN 7

int main()
{
    unsigned int t, i, day, max, total, basic, extra;
    scanf("%d", &t);

    while (t--)
    {
        day = max = 0;
        for ( i = 1; i <= WEEKLEN; ++i )
        {
            scanf("%d %d", &basic, &extra);
            total = basic + extra;
            if (total > 8 && total > max)
            {
                max = total;
                day = i;
            }
        }
        printf("%d\n", day);
    }

    return 0;
}