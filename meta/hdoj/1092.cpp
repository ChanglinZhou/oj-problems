#include <stdio.h>

int main()
{
    int n, m, sum;

    while (scanf("%d", &n) != EOF && n != 0)
    {
        sum = 0;
        while (n--)
        {
            scanf("%d", &m);
            sum += m;
        }
        printf("%d\n", sum);
    }

    return 0;
}