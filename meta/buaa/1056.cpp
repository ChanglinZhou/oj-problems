#include <stdio.h>

int main( )
{
    int a, b, c, d, e, f;
    while ( scanf("%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f) != EOF )
    {
        if ( a == 0 && b == 0 && c== 0
            && d == 0 && e ==0 && f == 0 )
            break;

        printf("%d\n", (d + 12 - a) * 60 * 60 + (e - b) * 60 + (f - c));
    }

    return 0;
}